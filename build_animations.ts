import fs from "fs";
import { parseGraphics } from "uqm-files-parsers";
import UPNG from '@pdf-lib/upng';
import Jimp from "jimp";
import mkdirp from "mkdirp";
import rimraf from "rimraf";
import { AnimationType, Graphics, AnimationsMap, Frame, Animation } from "uqm-files-parsers/dist/interfaces";
import shuffleSeed from "shuffle-seed";
import glob from "glob";
import path from "path";


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
    let frames = animation.frames; // default: AnimationType.CIRCULAR
    if (animation.type === AnimationType.YO_YO) {
      frames = frames.concat(frames.reverse());
    } else if (animation.type === AnimationType.RANDOM || animation.type === AnimationType.TALK) {
      for (let i = 0; i < 10; i++) {
        frames = frames.concat(frames);
      }
      frames = shuffleSeed.shuffle(frames, animation.name);
    } else if (animation.type === AnimationType.BACKGROUND && frames.length > 1) {
      throw new Error("AnimationType is BACKGROUND, but more than one frame specified in animation! This is not currently supported.");
      // TODO: for AnimationType.BACKGROUND, merge all frames?
    }
    const imgs = frames.map(f => imagesMap.get(f.frame_index));
    const deltas = frames.map(f => f.duration);
    const data = UPNG.encode(imgs, canvasWidth, canvasHeight, 0, deltas);
    fs.writeFileSync(animationPathFunc(animation.name), Buffer.from(data));
  }

  graphics.animations.forEach(animation => {
    saveAnimation(animation, graphics);
  });

  return graphics;
}

async function one_iter(anifilename) {
  const parsed_filename = path.parse(anifilename);
  console.log(`Parsing: ${parsed_filename.name}`);
  const out_folder = `${parsed_filename.dir}/anim_apng_out`;
  console.log(`Output folder: ${out_folder}`);
  rimraf.sync(out_folder);
  await mkdirp(out_folder);
  const anims = [];

  await parseGraphicsFile(anifilename, resolve_input => `./comm/${parsed_filename.name}/${resolve_input}`, aniname => {
    const retval = `${out_folder}/${aniname}.png`;
    anims.push(retval);
    return retval;
  });
  const html = `<html><head><style>* { position: absolute; top: 0px; left: 0px; }</style></head><body>${anims.map(fpath => {
    return `<img src="${fpath.split("/").pop()}"/>`;
  }).join("")}</body></html>`;
  fs.writeFileSync(`${out_folder}/index.html`, html);
  console.log(`Done with ${parsed_filename.name}.`);
}

async function main() {
  const files = glob.sync("./comm/**/*.ani");
  for (let fname of files) {
    await one_iter(fname);
  }
}

main().then(console.log).catch(console.error);
