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
var pluginName = "native_plugin";
var aimpFolder = "AIMP4.51";

var paths = {
    plugin: "./" + configuration,
    output: "../../../../" + aimpFolder + "/Plugins/" + pluginName
};

gulp.task("default",
    ["clean", "copy"],
    function() {
        // place code for your default task here
    });

gulp.task("copy", ["copy:plugin"]);

gulp.task("clean",
    function() {
        gulp.src(paths.output, { read: false })
            .pipe(clean({ force: true }));
    });

gulp.task("copy:plugin",
    function() {
        gulp.src([
                paths.plugin + "/*.dll"
            ])
            .pipe(gulp.dest(paths.output));
    });
