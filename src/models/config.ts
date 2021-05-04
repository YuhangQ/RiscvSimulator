import * as fs from "fs";
import * as path from "path";
import { jsonc } from "jsonc";

class Config {
    public static theme: string;
    public static fontFamily: string;
    public static fontSize: number;
    public static tabSize: number;
    public static insertSpaces: boolean;
    public static autoClosingBrackets: string;
    public static autoClosingQuotes: string;
    public static autoIndent: string;
    public static folding: boolean;
    public static lineNumbers: boolean;
    public static mouseWheelZoom: boolean;
    public static renderIndentGuides: boolean;
    public static minimap: boolean;
    public static autoComplete: boolean;
    public static json: JSON;
    public static path = path.join(__dirname, "../../config/config.json");
    public static examplePath = path.join(__dirname, "../../config/config-example.jsonc");

    public static init() {
        this.load(this.examplePath);
        this.json = this.load(this.path);
    }
    public static updateFontSize(size: number) {
        if(size <= 0) return;
        this.fontSize = size;
        this.json["fontSize"] = size;
        this.save();
    }
    public static save() {
        fs.writeFileSync(path.join(__dirname, "../../config/config.json"), jsonc.stringify(this.json, null, 4));
    }
    private static load(file: string): JSON {
        let json = jsonc.parse(fs.readFileSync(file).toString());
        if(json.theme) Config.theme = json.theme;
        if(json.fontFamily) Config.fontFamily = json.fontFamily;
        if(json.fontSize) Config.fontSize = json.fontSize;
        if(json.tabSize) Config.tabSize = json.tabSize;
        if(json.insertSpaces) Config.insertSpaces = json.insertSpaces;
        if(json.autoClosingBrackets) Config.autoClosingBrackets = json.autoClosingBrackets;
        if(json.autoClosingQuotes) Config.autoClosingQuotes = json.autoClosingQuotes;
        if(json.autoIndent) Config.autoIndent = json.autoIndent;
        if(json.folding) Config.folding = json.folding;
        if(json.lineNumbers) Config.lineNumbers = json.lineNumbers;
        if(json.mouseWheelZoom) Config.mouseWheelZoom = json.mouseWheelZoom;
        if(json.renderIndentGuides) Config.renderIndentGuides = json.renderIndentGuides;
        if(json.miniMap) Config.minimap = json.miniMap;
        if(json.autoComplete) Config.autoComplete = json.autoComplete;
        return json;
    }
}

export { Config }