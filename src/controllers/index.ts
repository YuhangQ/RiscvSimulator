/// <reference path="../../node_modules/monaco-editor/monaco.d.ts" />
import * as path from "path";

const core = require("../../sim-core/build/Release/core.node");

let consoleEl = document.getElementById("console") as HTMLInputElement;
let consoleToEnd = false;

let memBody = document.getElementById("membody");

let err = false;

loadComponents(() => {

    monaco.languages.register({ id: 'riscv' });
    monaco.languages.setMonarchTokensProvider('riscv', {
        tokenizer: {
            root: [
                [/\b(\-|\+)?\d+(\.\d+)?\b/, "custom-error"],
                [/\b(zero|ra|sp|gp|tp|t0|t1|t2|s0|fp|s1|a0|a1|a2|a3|a4|a5|a6|a7|s2|s3|s4|s5|s6|s7|s8|s9|s10|s11|t3|t4|t5|t6)\b/, "custom-notice"],
                [/^[\. a-zA-Z 0-9]+:/, "tag"],
                [/\b(addi|sd|sw|li|jr|lw|sext.w|addw|bge|ble|mulw|addiw|mv|ld|call|j|beq|bne)\b/, "custom-date"],
            ]
        }
    });

    monaco.editor.defineTheme('myTheme', {
        base: 'vs',
        inherit: false,
        rules: [
            { token: 'tag', foreground: 'a31515' },
            { token: 'custom-error', foreground: '09869e'},
            { token: 'custom-notice', foreground: 'FFA500' },
            { token: 'custom-date', foreground: '0000FF' },
        ],
        colors: {}
    });



    let editor = monaco.editor.create(document.getElementById("editor"), {
        value: `	.file	"test.c"
    .option nopic
    .attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
    .attribute unaligned_access, 0
    .attribute stack_align, 16
    .text
    .align	1
    .globl	main
    .type	main, @function
main:
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
    li	a5,100
    ble	a4,a5,.L3
    li	a5,0
    mv	a0,a5
    ld	s0,24(sp)
    addi	sp,sp,32
    jr	ra
    .size	main, .-main
    .ident	"GCC: (GNU) 10.2.0"`,
        language: "riscv",
        theme: "myTheme",
        automaticLayout: true,
        fontSize: 18,
        autoClosingBrackets: "always",
        autoIndent: "brackets",
        fontFamily: "Consolas, 'Microsoft YaHei', 黑体, 宋体",
        minimap: { enabled: false },
    })

    let decorations: string[] = [];

    document.getElementById("run").onclick = () => {

        err = false;
        memBody.innerHTML = "";
        consoleEl.value = "";

        document.getElementById("run").classList.add("disabled");
        document.getElementById("stop").classList.remove("disabled");
        document.getElementById("step").classList.remove("disabled");
        document.getElementById("end").classList.remove("disabled");

        core.setCodes(editor.getValue());


        let test = setInterval(() => {
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

        let line = core.curLine();
            decorations = editor.deltaDecorations(decorations, [
                { range: new monaco.Range(line, 1, line, 100000), options: { inlineClassName: 'myInlineDecoration' } },
            ]);
    }
    document.getElementById("step").onclick = () => {

        let curline = core.curLine();

        let res = core.nextStep();
        editor.revealLineInCenter(core.curLine());

        if(res) {
            let line = core.curLine();
            decorations = editor.deltaDecorations(decorations, [
                { range: new monaco.Range(line, 1, line, 100000), options: { inlineClassName: 'myInlineDecoration' } },
            ]);
        } else {
            decorations = editor.deltaDecorations(decorations, [
                { range: new monaco.Range(curline, 1, curline, 100000), options: { inlineClassName: 'errorDecoration' } },
            ]);
            document.getElementById("run").classList.remove("disabled");
            document.getElementById("stop").classList.add("disabled");
            document.getElementById("step").classList.add("disabled");
            document.getElementById("end").classList.add("disabled");
            err = true;
        }

        

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


        if(core.end()) {
            document.getElementById("run").classList.remove("disabled");
            document.getElementById("stop").classList.add("disabled");
            document.getElementById("step").classList.add("disabled");
            document.getElementById("end").classList.add("disabled");
            return;
        }

    }

    document.getElementById("stop").onclick = () => {
        document.getElementById("run").classList.remove("disabled");
            document.getElementById("stop").classList.add("disabled");
            document.getElementById("step").classList.add("disabled");
            document.getElementById("end").classList.add("disabled");
    }
    document.getElementById("end").onclick = () => {
        while(!core.end() && !err) {
            document.getElementById("step").click();
        }
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