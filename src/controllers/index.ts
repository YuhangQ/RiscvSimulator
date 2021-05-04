/// <reference path="../../node_modules/monaco-editor/monaco.d.ts" />
import * as path from "path";

const core = require("../../sim-core/build/Release/core.node");

let consoleEl = document.getElementById("console") as HTMLInputElement;
let consoleToEnd = false;

let memBody = document.getElementById("membody");

loadComponents(() => {
    let editor = monaco.editor.create(document.getElementById("editor"), {
        value: `.file	"test.c"
    .option nopic
    .attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
    .attribute unaligned_access, 0
    .attribute stack_align, 16
    .text
    .align	1
    .globl	hello
    .type	hello, @function
hello:
    addi	sp,sp,-32
    sd	s0,24(sp)
    addi	s0,sp,32
    sw	zero,-20(s0)
    li	a5,1
    sw	a5,-24(s0)
    j	.L2
.L3:
    lw	a4,-20(s0)
    lw	a5,-24(s0)
    addw	a5,a4,a5
    sw	a5,-20(s0)
    lw	a5,-24(s0)
    addiw	a5,a5,1
    sw	a5,-24(s0)
.L2:
    lw	a5,-24(s0)
    sext.w	a4,a5
    li	a5,50
    ble	a4,a5,.L3
    nop
    mv	a0,a5
    ld	s0,24(sp)
    addi	sp,sp,32
    jr	ra
    .size	hello, .-hello
    .align	1
    .globl	main
    .type	main, @function
main:
    addi	sp,sp,-32
    sd	ra,24(sp)
    sd	s0,16(sp)
    addi	s0,sp,32
    call	hello
    mv	a5,a0
    sw	a5,-20(s0)
    li	a5,51
    sw	a5,-24(s0)
    j	.L5
.L6:
    lw	a4,-20(s0)
    lw	a5,-24(s0)
    addw	a5,a4,a5
    sw	a5,-20(s0)
    lw	a5,-24(s0)
    addiw	a5,a5,1
    sw	a5,-24(s0)
.L5:
    lw	a5,-24(s0)
    sext.w	a4,a5
    li	a5,100
    ble	a4,a5,.L6
    li	a5,0
    mv	a0,a5
    ld	ra,24(sp)
    ld	s0,16(sp)
    addi	sp,sp,32
    jr	ra
    .size	main, .-main
    .ident	"GCC: (GNU) 10.2.0"`,
        language: "plain",
        automaticLayout: true,
        fontSize: 18,
        autoClosingBrackets: "always",
        autoIndent: "brackets",
        fontFamily: "Consolas, 'Microsoft YaHei', 黑体, 宋体",
        minimap: { enabled: false },
    })

    let decorations: string[] = [];

    document.getElementById("run").onclick = () => {

        memBody.innerHTML = "";
        consoleEl.value = "";

        document.getElementById("run").classList.add("disabled");
        document.getElementById("stop").classList.remove("disabled");
        document.getElementById("step").classList.remove("disabled");
        document.getElementById("end").classList.remove("disabled");

        core.setCodes(editor.getValue());


        let test = setInterval(() => {
            let line = core.curLine();
            decorations = editor.deltaDecorations(decorations, [
                { range: new monaco.Range(line, 1, line, 100000), options: { inlineClassName: 'myInlineDecoration' } },
            ]);


            for(let i=0; i<32; i++) {
                let arr = core.getRegister();
                document.getElementById("r"+i).innerHTML = arr[i];
            }


            consoleEl.value = consoleEl.value + core.getLogs();
            if(consoleToEnd) {
                consoleEl.scrollTop = consoleEl.scrollHeight;
                consoleToEnd = false;
            }

        }, 100);

        consoleToEnd = true;

        editor.revealLineInCenter(core.curLine());
    }
    document.getElementById("step").onclick = () => {

        

        core.nextStep();
        editor.revealLineInCenter(core.curLine());

        let line = core.curLine();
        decorations = editor.deltaDecorations(decorations, [
            { range: new monaco.Range(line, 1, line, 100000), options: { inlineClassName: 'myInlineDecoration' } },
        ]);
        consoleToEnd = true;

        memBody.innerHTML = "";

        let memArr = core.getUsedMemory();
        for(let mem of memArr) {
            let value = core.getMemory(mem);
            //console.log(mem +  "=" + value);

            let hex = "0x" + mem.toString(16);

            memBody.innerHTML += `<tr>
            <th scope="row">${hex}</th>
            <td id="m${hex}">${value}</td>
        </tr>`
            
        }

    }
    document.getElementById("end").onclick = () => {
        core.end();
        consoleToEnd = true;

        memBody.innerHTML = "";

        let memArr = core.getUsedMemory();
        for(let mem of memArr) {
            let value = core.getMemory(mem);
            let hex = "0x" + mem.toString(16);

            memBody.innerHTML += `<tr>
            <th scope="row">${hex}</th>
            <td id="m${hex}">${value}</td>
        </tr>`
        }

        document.getElementById("run").classList.remove("disabled");
        document.getElementById("stop").classList.add("disabled");
        document.getElementById("step").classList.add("disabled");
        document.getElementById("end").classList.add("disabled");
        
    }

    document.getElementById("stop").onclick = () => {
        document.getElementById("run").classList.remove("disabled");
        document.getElementById("stop").classList.add("disabled");
        document.getElementById("step").classList.add("disabled");
        document.getElementById("end").classList.add("disabled");
    }


});

/**
 * 初始化 monaco 编辑器
 * @param func 
 */
function loadComponents(func: Function) {

    const amdLoader = require('monaco-editor/dev/vs/loader.js');
    const amdRequire = amdLoader.require;
    function uriFromPath(_path) {
        var pathName = path.resolve(_path).replace(/\\/g, '/');
        if (pathName.length > 0 && pathName.charAt(0) !== '/') {
            pathName = '/' + pathName;
        }
        return encodeURI('file://' + pathName);
    }

    amdRequire.config({
        baseUrl: uriFromPath(path.join(__dirname, '../../node_modules/monaco-editor/dev'))
    });

    // workaround monaco-css not understanding the environment
    self.module = undefined;

    amdRequire(['vs/editor/editor.main'], func);
}