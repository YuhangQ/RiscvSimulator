import { Menu, app } from "electron";
import { mainWindow } from "../main";
function createMenu() {
    const template = [];
    template.push({
        label: "文件",
        submenu: [
            {
                label: "新建文件",
                click() { mainWindow.webContents.send("action", "new"); },
                accelerator: "CmdOrCtrl+N"
            },
            {
                enabled: false,
                label: "新建窗口",
                click() {},
                accelerator: "Shift+CmdOrCtrl+N"
            },
            { type: "separator" },
            {
                label: "打开",
                click() { mainWindow.webContents.send("action", "open"); },
                accelerator: "CmdOrCtrl+O"
            },
            { type: "separator" },
            {
                label: "保存未命名文件",
                click() { mainWindow.webContents.send("action", "save"); },
                accelerator: "CmdOrCtrl+S"
            },
            {
                label: "另存为",
                click() { mainWindow.webContents.send("action", "saveas") },
                accelerator: "Shift+CmdOrCtrl+S"
            },
            { type: "separator" },
            {
                label: "关闭标签页",
                click() { mainWindow.webContents.send("action", "closetag") },
                accelerator: "CmdOrCtrl+W"
            },
        ]
    });

    // Edit Menu
    template.push({
        label: "编辑",
        submenu: [
            { label: "撤销", role: "undo" },
            { label: "恢复", role: "redo" },
            { type: "separator" },
            { label: "剪切", role: "cut" },
            { label: "复制", role: "copy" },
            { label: "粘贴", role: "paste" },
        ]
    });

    // Windown menu
    template.push({
        label: "窗口",
        role: "window",
        submenu: [{ label: "最小化", role: "minimize" }]
    });
    template.push({
        label: "查看",
        submenu: [
            {
                label: "输入输出窗口",
                click() { mainWindow.webContents.send("action", "console"); },
                accelerator: "Ctrl+`"
            },
        ]
    });
    template.push({
        label: "运行",
        submenu: [
            { 
                enabled: false,
                label: "编译",
                click() { mainWindow.webContents.send("action", "compile"); },
                accelerator: "CmdOrCtrl+B"
            },
            {
                label: "编译并运行",
                click() { mainWindow.webContents.send("action", "cprun"); },
                accelerator: "F5"
            },
            {
                enabled: false,
                label: "开发者工具",
                click() { mainWindow.webContents.send("action", "devtools"); },
            }
        ]
    });
    template.push({
        label: "代码段",
        submenu: [
            { 
                enabled: false,
                label: "新建代码段",
                click() { mainWindow.webContents.send("action", "newSnippets"); },
            },
            {
                enabled: false,
                label: "查看所有代码段",
                click() { mainWindow.webContents.send("action", "cprun"); },
            },
            {
                enabled: false,
                label: "代码段帮助",
                click() { mainWindow.webContents.send("action", "devtools"); },
            }
        ]
    });
    // Help menu
    template.push({
        label: "帮助",
        role: "help",
        submenu: [
            {
                label: "访问我们的网站",
                click() {
                    require("electron").shell.openExternal("https://www.yuhangq.me/archives/35/");
                }
            }
        ]
    });

    if (process.platform === "darwin") {
        template.unshift({
            label: app.getName(),
            submenu: [
                { label: "关于 CubeText", role: "about" },
                { type: "separator" },
                { label: "设置", submenu: [
                    {
                        label: "设置",
                        click() { mainWindow.webContents.send("action", "settings"); }
                    },
                    {
                        label: "重置设置(当程序崩溃)",
                        click() { mainWindow.webContents.send("action", "remove-settings"); }
                    },
                    { type: "separator" },
                    {
                        label: "增大字体",
                        accelerator: "CmdOrCtrl+=",
                        click() { mainWindow.webContents.send("action", "font-larger"); }
                    },
                    { 
                        label: "减小字体",
                        accelerator: "CmdOrCtrl+-",
                        click() { mainWindow.webContents.send("action", "font-smaller"); }
                    },
                ] },
                { type: "separator" },
                { label: "服务", role: "services", submenu: [] },
                { type: "separator" },
                { label: "隐藏 CubeText", role: "hide" },
                { label: "隐藏其他", role: "hideothers" },
                { label: "全部显示", role: "unhide" },
                { type: "separator" },
                { label: "退出 CubeText",role: "quit" }
            ]
        });

        // Edit menu
        template[2].submenu.push(
            { type: "separator" },
            { label: "朗读", submenu: [{ label: "开始朗读", role: "startspeaking" }, { label: "停止朗读", role: "stopspeaking" }] }
        );

        // Window menu
        template[3].submenu = [{ label: "关闭", role: "close" }, { label: "最小化", role: "minimize" }, { label: "缩放", role: "zoom" }, { type: "separator" }, { label: "全部置于顶层", role: "front" }];
    } else {
        template[0].submenu.push(
            { label: "设置", submenu: [
                {
                    label: "设置",
                    click() { mainWindow.webContents.send("action", "settings"); }
                },
                {
                    label: "重置设置(当程序崩溃)",
                    click() { mainWindow.webContents.send("action", "remove-settings"); }
                },
                { type: "separator" },
                {
                    label: "增大字体",
                    accelerator: "CmdOrCtrl+=",
                    click() { mainWindow.webContents.send("action", "font-larger"); }
                },
                { 
                    label: "减小字体",
                    accelerator: "CmdOrCtrl+-",
                    click() { mainWindow.webContents.send("action", "font-smaller"); }
                },
            ] },
        )
    }

    let menu = Menu.buildFromTemplate(template);
    Menu.setApplicationMenu(menu);
}

export { createMenu };