import { MyTab } from "./mytab";
import { exec } from "child_process";
import * as path from "path";
import * as fs from "fs";
import { Utils } from "./utils";
class Runner {
    public static cprun(tab: MyTab) {

        let lang = tab.getLanguage().getLang();
        //alert(path.join(__dirname, "../../scripts/"+ lang +".bat"))
        let script = path.join(__dirname, "../../scripts/"+ lang +".bat");
        //alert(script);
        if(!fs.existsSync(script)) {
            alert("暂时不支持这种类型的文件运行.");
            return;
        }

        tab.save();

        let file = tab.getFile();

        let execFile = path.join(path.dirname(file), 
        path.basename(file, path.extname(file)));
        
        exec("start " + script + " " + Utils.pathWithQuotes(file) + " " + Utils.pathWithQuotes(execFile) + " " + Utils.pathWithQuotes(path.dirname(file)));
    }
}

export { Runner }