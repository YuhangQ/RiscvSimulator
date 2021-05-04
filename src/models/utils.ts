import * as iconv from "iconv-lite";
import * as os from "os";
import * as fs from "fs";

class Utils {
    /**
     * 根据路径获取文件名
     * @param path
     */
    public static linefeed: string;
    public static seperator: string;
    static init() {
        if(this.isWindows()) {
            this.linefeed = "\r\n";
            this.seperator = "\\";
        } else if(this.isMacos()) {
            this.linefeed = "\n";
            this.seperator = "/";
        } else {
            this.linefeed = "\n";
            this.seperator = "/";
        }
    }
    static getFileNameByPath(path: string): string {
        var pos1 = path.lastIndexOf("/");
        var pos2 = path.lastIndexOf("\\");
        var pos  = Math.max(pos1, pos2)
        if(pos < 0) return path;
        else return path.substring(pos + 1);
    }
    static transtoPath(path: string): string {
        return path;
    }
    static pathWithQuotes(str: string): string {
        return "\"" + str + "\"";
    }
    static removeShellChar(s: string) {
        if(this.isWindows()) {
            let arr = s.match(/\[\w\w|\[\?\w\w\w/g);
            if(arr) for(let v of arr) s = s.replace(v, "");
        } else {
            let arr = s.match(/\[0;1;3\dm|\[\dm|\[0;3\dm/g);
            if(arr) for(let v of arr) if(v) s = s.replace(v, "");
        }
        return s;
    }
    static encode(s: string): string {
        s = this.removeShellChar(s);
        if(this.isWindows()) {
            let buf = iconv.encode(s, "gbk");
            let str = iconv.decode(buf, "utf-8");
            return str;
        } else {
            return s;
        }
    }
    static makeFileIfnotExsits(file: string) {
        if(!fs.existsSync(file)) {
            fs.writeFileSync(file, "");
        }
    }
    static isWindows() {
        return os.platform() === "win32";
    }
    static isMacos() {
        return os.platform() === "darwin";
    }
    static isLinux() {
        return os.platform() === "linux";
    }
}

export { Utils };