import fs from "fs";
import { parseGraphics } from "uqm-files-parsers";
import UPNG from '@pdf-lib/upng';
import Jimp from "jimp";
import mkdirp from "mkdirp";
import rimraf from "rimraf";

// bleh; uqm-files-parsers does not export the types, so we gotta manually reconstruct 'em here!
type Graphics = ReturnType<typeof parseGraphics>;
type AnimationsMap = Graphics["animations"];
type Frame = Graphics["frames"][0];
type Animation = ReturnType<AnimationsMap["get"]>;

async function parseGraphicsFile(filename: string, fileResolver: (input: string) => string, animationPathFunc: (input: string) => string) {
  const graphics = parseGraphics(fs.readFileSync(filename).toString());
  const framesMap: Map<number, Frame> = new Map();
  const jimpImagesMap: Map<number, Jimp> = new Map();
  const imagesMap: Map<number, ArrayBuffer> = new Map();
  let canvasWidth = 0;
  let canvasHeight = 0;

  let i = 0;
  for (let frame of graphics.frames.values()) {
    framesMap.set(i, frame);
    const j = await Jimp.read(fileResolver(frame.filename));
    jimpImagesMap.set(i, j);
    i += 1;
  };

  // compute sizes.
  // TODO: compute including hotspots!?
  jimpImagesMap.forEach(frame => {
    if (canvasWidth < frame.getWidth()) {
      canvasWidth = frame.getWidth();
    }
    if (canvasHeight < frame.getHeight()) {
      canvasHeight = frame.getHeight();
    }
  });

  i = 0;
  for (let frame of jimpImagesMap.values()) {
    const jRoot = await Jimp.create(canvasWidth, canvasHeight);
    await jRoot.blit(frame, 0 - framesMap.get(i).hotspot.x, 0 - framesMap.get(i).hotspot.y);
    imagesMap.set(i, jRoot.bitmap.data.buffer);
    i += 1;
  }

  function saveAnimation(animation: Animation, graphics: Graphics) {
    // TODO: support different animation types!
    const imgs = animation.frames.map(f => imagesMap.get(f.frame_index));
    const deltas = animation.frames.map(f => f.duration);
    const data = UPNG.encode(imgs, canvasWidth, canvasHeight, 0, deltas);
    fs.writeFileSync(animationPathFunc(animation.name), Buffer.from(data));
  }

  graphics.animations.forEach(animation => {
    saveAnimation(animation, graphics);
  });

  return graphics;
}

async function main() {
  rimraf.sync("./out");
  await mkdirp("./out");
  const anims = [];
  await parseGraphicsFile("./comm/chmmr/chmmr.ani", fname => `./comm/chmmr/${fname}`, aniname => {
    const retval = `./out/${aniname}.png`;
    anims.push(retval);
    return retval;
  });
  const html = `<html><head><style>* { position: absolute; top: 0px; left: 0px; }</style></head><body>${anims.map(fpath => {
    return `<img src="${fpath.split("/").pop()}"/>`;
  }).join("")}</body></html>`;
  fs.writeFileSync("./out/index.html", html);
}

main().then(console.log).catch(console.error);
