import glob from "glob";
import fs from "fs";
import path from "path";
import { parseGraphics } from "uqm-files-parsers";
import UPNG from '@pdf-lib/upng';
import Jimp from "jimp";
import mkdirp from "mkdirp";
import rimraf from "rimraf";
import { AnimationType, Graphics, AnimationsMap, Frame, Animation } from "uqm-files-parsers/dist/interfaces";
import shuffleSeed from "shuffle-seed";


async function buildFont(dir: string) {
  const jimpImagesMap: Map<number, Jimp> = new Map();
  let charWidth = 0;
  let charHeight = 0;
  let minCharCode = Infinity;
  let maxCharCode = 0;


  const files = glob.sync(path.join(dir, '*.png'));

  let i = 0;
  await Promise.all(files.map(async file => {
    const j = await Jimp.read(file);
    jimpImagesMap.set(parseInt(path.basename(file).split('.').shift(), 16), j);
  }));

  // compute sizes.

  Array.from(jimpImagesMap.entries()).forEach(entry => {
    const charCode = entry[0];
    const frame = entry[1];
    if (charWidth < frame.getWidth()) {
      charWidth = frame.getWidth();
    }
    if (charHeight < frame.getHeight()) {
      charHeight = frame.getHeight();
    }
    if (charCode < minCharCode) {
      minCharCode = charCode;
    }
    if (charCode > maxCharCode) {
      maxCharCode = charCode;
    }
  });

  const BUF = 2;
  const OFF = 1;
  const jRoot = await Jimp.create((charWidth + BUF) * ((maxCharCode - minCharCode) + 1) + OFF*2, charHeight + BUF, "#FF00FFFF");
  function getXY(charCode: number) {
    const x = ((charCode - minCharCode) * (charWidth + BUF)) + Math.floor(BUF / 2) + OFF;
    const y = Math.floor(BUF / 2);
    return { x, y };
  }
  for (let i = minCharCode; i <= maxCharCode; i++) {
    const { x, y } = getXY(i);
    jRoot.scan(x, y, charWidth, charHeight, (x, y, offset) => {
      jRoot.bitmap.data.writeUInt32BE(0x00000000, offset);
    });
  };
  Array.from(jimpImagesMap.entries()).forEach(entry => {
    const charCode = entry[0];
    const frame = entry[1];
    const { x, y } = getXY(charCode);
    jRoot.blit(frame, x, y);
  });

  await jRoot.writeAsync(`${dir}.png`);
}

async function main() {
  const dirs = glob.sync("./fonts/*.fon");
  await Promise.all(Array.from(dirs).map((dir: string) => {
    return buildFont(dir);
  }));
}

main().then(console.log).catch(console.error);
