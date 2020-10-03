import glob from "glob";
import fs from "fs";
import path from "path";
import { parseTextLocalizationFile, parseTextSynchronizationFile } from "uqm-files-parsers";
import getAudioDurationInSeconds from "get-audio-duration";

const files = glob.sync("./comm/**/*.txt");


async function main() {
    files.forEach(async file => {
        try {
            const alienname = `${path.basename(file).split(".").shift()}`;
            const base = path.join(path.dirname(file), alienname);
            const commFile = fs.readFileSync(file).toString();
            const timingsFile = fs.readFileSync(`${base}.ts`).toString();
            await transform(timingsFile, commFile, base);
        } catch (e) {
            console.error(e);
            console.warn(`Could not parse ${file}`);
        }
    });
}

async function transform(timings, comm, base) {
    const dirname = path.dirname(base);
    const localization = parseTextLocalizationFile(comm);
    const synchronization = parseTextSynchronizationFile(timings);
    const entries = Array.from(localization.entries());
    const rmap = await entries.reduce(async (memoPromise, entry) => {
        const memo = await memoPromise;
        const synch = synchronization.get(entry[0]);

        let dur = null;
        if (entry[1].audioFile && synch !== undefined) {
            dur = await getAudioDurationInSeconds(path.join(dirname, entry[1].audioFile)) * 1000;
            dur = Math.ceil(dur);
            synch.timings.push(dur - synch.timings.reduce((m, v) => m + v, 0));
        }
        let start = 0;

        const lineTimings = entry[1].localizedText.split(/\n/).reduce((mem, line, i) => {
            if (synch === undefined) {
                return mem;
            }
            const d = synch.timings[i];
            mem.end += d;
            const r = {
                line,
                duration: d,
                start: mem.start,
                end: mem.end,
            };
            mem.lines.push(r);
            mem.start += d;
            return mem;
        }, { start: 0, end: 0, lines: [] }).lines;
        memo[entry[0]] = { ...entry[1], ...synch, audioFileDuration: dur, lineTimings };

        return memo;
    }, Promise.resolve({}));

    fs.writeFileSync(`${base}.json`, JSON.stringify(rmap, null, 2));
    return rmap;
}

main().then(console.log).catch(console.error);