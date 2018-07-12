/// <binding AfterBuild='copy' />
/*
This file is the main entry point for defining Gulp tasks and using Gulp plugins.
Click here to learn more. https://go.microsoft.com/fwlink/?LinkId=518007
*/

var gulp = require("gulp");
var gulpRename = require("gulp-rename");
var gulpCopy = require("gulp-copy");
var concat = require("gulp-concat");
var clean = require("gulp-clean");

var configuration = "Debug";
var pluginName = "dotnet_SmartPlaylist";
var aimpFolder = "AIMP4.51";

var paths = {
    plugin: "./bin/" + configuration,
    output: "../../../../" + aimpFolder + "/Plugins/" + pluginName
};

var sdk = {
    aimp_sdk: paths.plugin + "/AIMP.SDK.dll",
    aimp_dotnet: paths.plugin + "/aimp_dotnet.dll"
};

var langs = [
    "english",
    "russian"
];

gulp.task("default",
    ["clean", "copy"],
    function() {
        // place code for your default task here
    });

gulp.task("copy", ["copy:core", "copy:plugin", "copy:langs"]);

gulp.task("clean",
    function() {
        gulp.src(paths.output, { read: false })
            .pipe(clean({ force: true }));
    });

gulp.task("copy:core",
    function() {
        gulp.src(sdk.aimp_sdk).pipe(gulp.dest(paths.output));
        gulp.src(sdk.aimp_dotnet)
            .pipe(gulpRename(pluginName + ".dll"))
            .pipe(gulp.dest(paths.output));
    });

gulp.task("copy:plugin",
    function() {
        gulp.src([
                paths.plugin + "/*.dll",
                "!" + paths.plugin + "/AIMP.SDK.dll",
				"!" + paths.plugin + "/aimp_dotnet.dll",
                "!" + paths.plugin + "/" + pluginName + ".dll"
            ])
            .pipe(gulp.dest(paths.output));
        gulp.src(paths.plugin + "/" + pluginName + ".dll")
            .pipe(gulpRename(pluginName + "_plugin.dll"))
            .pipe(gulp.dest(paths.output));
    });

gulp.task("copy:langs",
    function() {
        var sdkLangsPath = "../aimp_dotnet/src/aimp_dotnet/Langs/";

        for (var i = 0; i < langs.length; i++) {
            gulp.src([
                    sdkLangsPath + langs[i] + ".lng",
                    "./Langs/" + langs[i] + ".lng",
                ])
                .pipe(concat(langs[i] + ".lng"))
                .pipe(gulp.dest(paths.output + "/Langs"));
        }
    });
