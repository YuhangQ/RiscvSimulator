import { app, BrowserWindow, ipcMain} from "electron";

let mainWindow: BrowserWindow;

function createWindow() {
	mainWindow = new BrowserWindow({
		width: 800,
		height: 600,
		webPreferences: {
			nodeIntegration: true
		}
	});
	//AppMenu.createMenu();
	mainWindow.setMenuBarVisibility(false);
	mainWindow.loadURL(`file://${__dirname}/../views/index.html`);
	//mainWindow.webContents.openDevTools();
}

app.on('ready', createWindow);

app.on('window-all-closed', function () {
	if (process.platform !== 'darwin') {
		app.quit();
	}
});

app.on('activate', function () {
	if (mainWindow === null) {
		createWindow()
	}
})


export { mainWindow }