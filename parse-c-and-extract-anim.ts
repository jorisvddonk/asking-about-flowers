import glob from "glob";
import fs from "fs";
import path from "path";
import { parseCommSrc } from "uqm-files-parsers";
import { AnimationType, CAnim } from "uqm-files-parsers/dist/interfaces";

const files = glob.sync("./comm/**/*.c");


async function main() {
  files.forEach(async file => {
    try {
      const dirname = path.basename(path.dirname(file));
      const base = path.dirname(file);
      const anifilepath = path.join(base, `${dirname}.ani`);
      const cfile = fs.readFileSync(file).toString();
      const anifile = fs.readFileSync(anifilepath).toString();
      await transform(cfile, anifile, anifilepath);
    } catch (e) {
      console.warn(`Could not parse ${file}`);
    }
  });
}

let CUR_ANI = 0;

function getAnimType(anim: CAnim) {
  if (anim.anim_type === AnimationType.YO_YO) {
    return 'YO_YO'
  } else if (anim.anim_type === AnimationType.RANDOM) {
    return 'RANDOM'
  } else if (anim.anim_type === AnimationType.CIRCULAR) {
    return 'CIRCULAR'
  } else if (anim.anim_type === AnimationType.TALK) {
    return 'TALK' // ?? is this correct!?
  } else if (anim.anim_type === AnimationType.BACKGROUND) {
    return 'BACKGROUND'
  }
}

function getAniDef(anim: CAnim) {
  return `#@ anidef ${CUR_ANI} ${getAnimType(anim)} ${anim.restart_rate_min} ${anim.restart_rate_max} ${anim.block_mask} [anim_${CUR_ANI}]`;
}

function getFrames(anim: CAnim, framelines: string[]) {
  const retval = [];
  for (let i = anim.start_index; i < anim.start_index + anim.num_frames; i++) {
    retval.push(`#@ aniframe ${CUR_ANI} ${anim.frame_rate_min} [${framelines[i]}]`);
  }
  return retval;
}

function transformAnim(anim: CAnim, framelines: string[]) {
  const retval = { def: getAniDef(anim), frames: getFrames(anim, framelines) }
  CUR_ANI += 1;
  return retval;
}

async function transform(cfile, anifile, anifilepath) {
  const framelines = anifile.split(/\r?\n/).map(x => x.trim()).filter(x => x !== undefined && x.length > 0 && x[0] !== '#');

  const animInfo = parseCommSrc(cfile);
  const anideflines = [];
  const aniframelines = [];

  const parseAnim = (anim: CAnim) => {
    const t_anim = transformAnim(anim, framelines);
    anideflines.push(t_anim.def);
    t_anim.frames.forEach(frame => aniframelines.push(frame));
  }

  parseAnim({
    anim_type: AnimationType.BACKGROUND,
    start_index: 0,
    num_frames: 1,
    block_mask: 0,
    frame_rate_max: 0,
    frame_rate_min: 0,
    restart_rate_max: 0,
    restart_rate_min: 0,
    wait_talk: false
  });
  animInfo.ambient_animations.forEach(anim => parseAnim(anim));
  animInfo.talk_animation.anim_type = AnimationType.TALK; // TODO: fix in parser!?
  parseAnim(animInfo.talk_animation);

  const outfilecontents = framelines.concat(anideflines).concat(aniframelines).join('\n');
  fs.writeFileSync(anifilepath, outfilecontents);
}

main().then(console.log).catch(console.error);