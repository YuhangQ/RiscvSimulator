import { remote } from "electron";
import { MyTab } from "./mytab";
import * as fs from "fs";

class FileHandler {
    static openFile() {
        remote.dialog.showOpenDialog(remote.getCurrentWindow(), {
            filters: [
                { name: 'All Files', extensions: ['*'] }],
            properties: ['openFile', 'multiSelections']
        }).then(result => {
            for(let file of result.filePaths) {
                MyTab.create(file);
            }
        })
    }
    static readText(file: string): string {
        return fs.readFileSync(file).toString();
    }

    static saveText(file: string, content: string) {
        fs.writeFileSync(file, content);
    }

    static getFileType(file: string) {
        
    }
}

export { FileHandler }