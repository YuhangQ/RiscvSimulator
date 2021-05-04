class Language {
    private name: string;
    private lang: string;
    private suffixs: string[];
    constructor(name: string, lang: string, suffixs: string[]) {
        this.name = name;
        this.lang = lang;
        this.suffixs = suffixs;
    }

    getSuffixs(): string[] {
        return this.suffixs;
    }
    getName(): string {
        return this.name;
    }
    getLang(): string {
        return this.lang;
    }

    private static array: Language[] = [];
    private static default: Language;

    public static getLanguageBySuffix(suffix: string): Language {
        //alert(suffix);
        for(let lang of this.array) {
            for(let suf of lang.getSuffixs()) {
                if(suffix.toLowerCase() == ("." + suf))
                    return lang;
            }
        }
        return this.default;
    }

    public static init() {
        this.array.push(new Language("C++", "cpp", 
        ["cpp", "cc", "hpp", "h", "cxx", "c++"]));
        this.array.push(new Language("Batch", "bat", ["bat", "cmd"]));
        this.array.push(new Language("C#", "csharp", ["cs"]));
        this.array.push(new Language("C", "c", ["c"]));
        this.array.push(new Language("CSS", "css", ["css"]));
        this.array.push(new Language("Go", "go", ["go"]));
        this.array.push(new Language("HTML", "html", ["html", "htm"]));
        this.array.push(new Language("JSON", "json", ["json"]));
        this.array.push(new Language("INI", "ini", ["ini"]));
        this.array.push(new Language("Java", "java", ["java"]));
        this.array.push(new Language("JavaScript", "javascript", ["js"]));
        this.array.push(new Language("Lua", "lua", ["lua"]));
        this.array.push(new Language("Markdown", "markdown", ["md"]));
        this.array.push(new Language("PHP", "php", ["php"]));
        this.array.push(new Language("Python", "python", ["py"]));
        this.array.push(new Language("Shell", "shell", ["sh"]));
        this.array.push(new Language("TypeScript", "typescript", ["ts"]));
        this.array.push(new Language("XML", "xml", ["xml"]));
        this.array.push(new Language("YAML", "yaml", ["yml", "yaml"]));
        this.default = new Language("Plain", "plaintext", []);
    }
}

export { Language }