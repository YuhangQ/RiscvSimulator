import * as TabGroup from "electron-tabs";
import * as dragula from "dragula";
import { Utils } from "../models/utils";
import { FileHandler } from "./filehandler";
import { remote, ipcRenderer } from "electron"
import * as path from "path";
import { Language } from "./language";
import { Config } from "./config";
class MyTab {
    private static tabGroup: TabGroup;
    private static tabs: { [key: number]: MyTab } = {};
    private static jsonExample: monaco.editor.IStandaloneCodeEditor;
    public static init() {
        this.tabGroup = new TabGroup({
            ready: function (tabGroup) {
                dragula([tabGroup.tabContainer], {
                    direction: "horizontal"
                });
            }
        });
        this.tabGroup.on("tab-active", (tab, tabGroup) => {
            MyTab.getTab(tab.id).show();
            for (let id in MyTab.tabs) {
                if (id != tab.id) MyTab.tabs[id].hide();
            }
            if(MyTab.getTab(tab.id).getFile() == Config.path) {
                document.getElementById("config-example").hidden = false;
                //document.getElementById("container").style.width = "50vw";
                //MyTab.getTab(tab.id).getElement().style.width = "50vw";
            } else {
                document.getElementById("config-example").hidden = true;
                //document.getElementById("container").style.width = "100vw";
                //MyTab.getTab(tab.id).getElement().style.width = "50vw";
            }
            MyTab.getTab(tab.id).getEditor().focus();
        });
        this.tabGroup.on("tab-removed", (tab, tabGroup) => {
            if (this.tabGroup.getTabs().length == 0) {
                MyTab.createUntitled();
            }
        });

        // 拖拽打开文件
        var holder = document.getElementsByTagName("body")[0];
        holder.ondragover = function () {
            return false;
        };
        holder.ondragleave = holder.ondragend = function () {
            return false;
        };

        holder.ondrop = function (e) {
            e.preventDefault();
            for (let i = 0; i < e.dataTransfer.files.length; i++) {
                let file = e.dataTransfer.files[i];
                MyTab.create(file.path);
            }
            return false;
        };
        // 用于自动保存
        setInterval(MyTab.saveAll, 2000);
    }
    public static setExampleEditor(editor: monaco.editor.IStandaloneCodeEditor) {
        this.jsonExample = editor;
    }
    public static create(file: string) {

        // 防止重复打开
        for (let tab of this.getTabs()) {
            if (tab.getFile() == file) {
                tab.activate();
                return;
            }
        }

        let untitledTab: MyTab = undefined;
        if (this.getTabs().length == 1
            && this.getActiveTab().isUntitled()
            && !this.getActiveTab().isChanged()) {
            untitledTab = this.getActiveTab();
        }

        let tab = new MyTab(file);
        this.tabs[tab.getID()] = tab;
        tab.activate();
        tab.bindClose();

        if (untitledTab) untitledTab.close();

        if(tab.getFile() == Config.path) {
            tab.getElement().style.width = "50vw";
        }
    }
    public static createUntitled() {
        let tab = new MyTab("untitled", true);
        this.tabs[tab.getID()] = tab;
        tab.activate();
        tab.bindClose();
    }

    public static getTabs(): MyTab[] {
        let array: MyTab[] = [];
        for (let id in MyTab.tabs) {
            array.push(MyTab.tabs[id]);
        }
        return array;
    }

    public static getActiveTab(): MyTab {
        return this.tabs[this.tabGroup.getActiveTab().id];
    }

    public static getTab(id: number): MyTab {
        return this.tabs[id];
    }

    public static saveAll() {
        if(MyTab.getActiveTab().getEditor().getRawOptions().fontSize != Config.fontSize) {
            Config.updateFontSize(this.getActiveTab().getEditor().getRawOptions().fontSize);
        }
        for (let id in MyTab.tabs) {
            let tab = MyTab.tabs[id];
            tab.save();
        }
    }

    public static getFontSize(): number {
        return Config.fontSize;
    }
    public static setFontSize(size: number) {
        Config.updateFontSize(size);
        if(size <= 0) return;
        for (let tab of MyTab.getTabs()) {
            tab.editor.updateOptions({
                "fontSize": size
            })
        }
        this.jsonExample.updateOptions({
            "fontSize": size
        });
    }


    private tab: TabGroup.Tab;
    private editor: monaco.editor.IStandaloneCodeEditor;
    private element: HTMLDivElement;
    private status: HTMLDivElement;
    private untitled: boolean
    private file: string;
    private changed = false;

    private constructor(file: string, untitled = false) {
        this.file = file;
        this.untitled = untitled;
        this.tab = MyTab.tabGroup.addTab({
            title: Utils.getFileNameByPath(file),
            src: `file://${__dirname}/../../views/vscode.html`,
            visible: true,
            active: false
        });

        // 处理 HTML 元素
        let container = document.getElementById("container");

        this.element = document.createElement("div");
        this.element.setAttribute("id", "editor" + this.tab.id);
        this.element.setAttribute("class", "editor");

        this.status = document.createElement("div");
        this.status.setAttribute("id", "status" + this.tab.id);
        this.status.setAttribute("class", "status");

        let langEl = document.createElement("div");
        langEl.setAttribute("class", "status-lang");
        langEl.onmouseenter = () => { langEl.style.backgroundColor = "#177ec4" };
        langEl.onmouseleave = () => { langEl.style.backgroundColor = "#0063a6" };

        let encodingEl = document.createElement("div");
        encodingEl.setAttribute("class", "status-encoding");
        encodingEl.onmouseenter = () => { encodingEl.style.backgroundColor = "#177ec4" };
        encodingEl.onmouseleave = () => { encodingEl.style.backgroundColor = "#0063a6" };

        let lineEl = document.createElement("div");
        lineEl.setAttribute("class", "status-line");
        lineEl.onmouseenter = () => { lineEl.style.backgroundColor = "#177ec4" };
        lineEl.onmouseleave = () => { lineEl.style.backgroundColor = "#0063a6" };

        let messageEl = document.createElement("div");
        messageEl.setAttribute("class", "status-message");
        messageEl.onmouseenter = () => { messageEl.style.backgroundColor = "rgb(50, 145, 113)" };
        messageEl.onmouseleave = () => { messageEl.style.backgroundColor = "rgb(22, 130, 93)" };

        this.status.appendChild(langEl);
        this.status.appendChild(messageEl);
        this.status.appendChild(encodingEl);
        this.status.appendChild(lineEl);

        container.appendChild(this.element);
        container.appendChild(this.status);


        let content = "";
        if (!this.untitled) {
            content = FileHandler.readText(file);
        }

        //let b = 
        this.editor = monaco.editor.create(this.element, {
            value: content,
            language: this.getLanguage().getLang(),
            automaticLayout: true,
            theme: Config.theme,
            fontSize: MyTab.getFontSize(),
            autoClosingBrackets: "always",
            autoIndent: "brackets",
            mouseWheelZoom: Config.mouseWheelZoom,
            fontFamily: Config.fontFamily,
            //useTabStops: Config.tabSize
            //useTabStops: false,
            //glyphMargin: true,
            folding: Config.folding,
            renderIndentGuides: Config.renderIndentGuides,
            minimap: {enabled: Config.minimap},
        });
        this.editor.getModel().updateOptions({
            tabSize: Config.tabSize,
            insertSpaces: Config.insertSpaces,
        });
        //this.editor.trigger('editor','hideSuggestWidget', []);
        this.editor.onDidChangeModelContent(() => {
            this.changed = true;
            if (this.isUntitled()) {
                this.setTitle("untitled*");
            }
        })

        //monaco.editor.on
        this.editor.onDidChangeCursorPosition(() => {
            this.updateStatus();
        });

        // 获取焦点
        this.editor.focus();

        /*
        var decorations = this.editor.deltaDecorations([], [
            {
                range: new monaco.Range(3, 1, 3, 1),
                options: {
                    isWholeLine: false,
                    className: 'myContentClass',
                    glyphMarginClassName: 'myGlyphMarginClass'
                }
            }
        ]);
        */
        

        this.editor.onMouseDown((e) => {
            const data = e.target.detail;
            if (e.target.type !== monaco.editor.MouseTargetType.GUTTER_GLYPH_MARGIN) {
                return;
            }
            console.log(e);
        });

        this.updateStatus();
    }

    /**
     * 获取标签页的唯一标识
     */
    public getID(): number {
        return this.tab.id;
    }

    public close() {
        if(this.getFile() == Config.path) {
            let choice = remote.dialog.showMessageBoxSync(remote.getCurrentWindow(), {
                title: "修改了配置，是否关闭此程序并重新启动？",
                buttons: ["关闭程序", "稍后重启"],
                message: "修改了配置，是否关闭此程序并重新启动？",
                detail: "如果不重启，您的修改不会生效",
                cancelId: 2
            })
            // 保存
            if (choice == 0) {
                ipcRenderer.send("quit");
            } else if (choice == 1) {
                this.clear();
            }
        }
        if (this.isUntitled() && this.isChanged()) {
            let choice = remote.dialog.showMessageBoxSync(remote.getCurrentWindow(), {
                title: "是否保存",
                buttons: ["保存", "放弃"],
                message: "未命名文件被修改，是否保存？",
                detail: "选择放弃，将永久失去里面的信息.",
                cancelId: 2
            })
            // 保存
            if (choice == 0 && this.saveFile()) {
                this.clear();
            } else if (choice == 1) {
                this.clear();
            }
        } else {
            this.clear();
        }
    }

    public saveFile(): boolean {
        if (!this.isUntitled()) return false;
        let file = remote.dialog.showSaveDialogSync(remote.getCurrentWindow(), {
            title: "保存"
        });
        if (file) {
            this.setFile(file);
            this.setUntitled(false);
            //this.updateStatus();
            this.save();
            return true;
        } else {
            return false;
        }
    }

    private clear() {
        this.save();
        delete MyTab.tabs[this.tab.id];
        this.element.remove();
        this.tab.close();
    }

    private bindClose() {
        let button = document.getElementsByClassName("etabs-tab visible active")[0].getElementsByClassName("etabs-tab-button-close")[0] as HTMLElement;
        let clone = button.cloneNode(true);
        button.parentNode.replaceChild(clone, button);
        clone.addEventListener("click", this.close.bind(this));
    }

    public hide() {
        this.element.style.zIndex = "0";
        this.status.style.zIndex = "0";
    }
    public show() {
        this.element.style.zIndex = "1";
        this.status.style.zIndex = "1";
    }
    public activate() {
        this.tab.activate();
    }
    
    public getLanguage(): Language {
        return Language.getLanguageBySuffix(path.extname(this.file));
    }
    public isUntitled(): boolean {
        return this.untitled;
    }
    public setUntitled(untitled: boolean) {
        this.untitled = untitled;
    }
    public getFile(): string {
        return this.file;
    }
    public setFile(file: string) {
        this.file = file;
        this.setTitle(Utils.getFileNameByPath(file));
        monaco.editor.setModelLanguage(this.editor.getModel(), this.getLanguage().getLang());
        this.updateStatus();
    }
    public isChanged(): boolean {
        return this.changed;
    }
    public setTitle(title: string) {
        this.tab.setTitle(title);
    }
    public getElement() {
        return this.element;
    }
    public getTitle(): string {
        return this.tab.getTitle();
    }
    public save() {
        if (!this.changed) return;
        if (this.isUntitled()) return;
        FileHandler.saveText(this.file, this.editor.getModel().getValue());
        this.changed = false;
    }
    public updateStatus() {
        this.status.getElementsByClassName("status-message")[0].innerHTML
            = "&nbsp;&nbsp;<\\>&nbsp;&nbsp;";
        this.status.getElementsByClassName("status-lang")[0].innerHTML
            = this.getLanguage().getName();
        this.status.getElementsByClassName("status-encoding")[0].innerHTML
            = "UTF-8";
        this.status.getElementsByClassName("status-line")[0].innerHTML
            = "&nbsp;" + "行 " + this.editor.getPosition().lineNumber + ", 列 " + this.editor.getPosition().column + "&nbsp;";
    }
    public getEditor() {
        return this.editor;
    }
    public saveAs() {
        if (this.isUntitled()) {
            this.saveFile();
            return;
        }
        let file = remote.dialog.showSaveDialogSync(remote.getCurrentWindow(), {
            title: "另存为"
        });
        if (file) {
            this.setFile(file);
            this.changed = true;
            this.save();
            this.updateStatus();
        }
    }
}

export { MyTab };