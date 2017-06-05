var path = require('path');
var gulp = require('gulp');
var sass = require("gulp-sass");
var minify = require('gulp-minify-css');
var rename = require('gulp-rename');
var concat = require('gulp-concat');
var copy = require('gulp-copy');

var vendor = {
  css: ['bower_components/bootstrap/dist/css/bootstrap.css',
        'bower_components/highlightjs/styles/github-gist.css'
       ],
  js: ['bower_components/jquery/dist/jquery.min.js',
       'bower_components/bootstrap/dist/js/bootstrap.min.js',
       'bower_components/highlightjs/highlight.pack.min.js',
       'bower_components/lunr.js/lunr.min.js',
       'bower_components/js-url/url.min.js',
       'bower_components/twbs-pagination/jquery.twbsPagination.min.js',
       "bower_components/mark.js/dist/jquery.mark.min.js"
      ],
  webWorker: {
    src: ['lunr.min.js'],
    cwd: 'bower_components/lunr.js/'
  },
  font: {
    src: ['*'],
    cwd: 'bower_components/bootstrap/dist/fonts/'
  },
  maincss: {
      css: ['template/sass/docfx.scss',
            'template/sass/main.scss'
      ]
  }
}

gulp.task('concat', function () {
  gulp.src(vendor.css)
    .pipe(minify({keepBreaks: true}))
    .pipe(rename({
        suffix: '.min'
    }))
    .pipe(concat('docfx.vendor.css'))
    .pipe(gulp.dest('./template/styles/'))
  ;
  gulp.src(vendor.js)
    .pipe(concat('docfx.vendor.js'))
    .pipe(gulp.dest('./template/styles/'))
  ;
});

gulp.task('copy', function () {
  gulp.src(vendor.font.src, {cwd: vendor.font.cwd})
    .pipe(copy('./template/fonts/'))
  ;
  gulp.src(vendor.webWorker.src, {cwd:vendor.webWorker.cwd})
    .pipe(copy('./template/styles/'))
  ;
});

gulp.task('default', ['concat', 'copy', 'sass']);

gulp.task('sass', function() {
    gulp.src(vendor.maincss.css)
    .pipe(sass().on('error', sass.logError))
    .pipe(gulp.dest('./template/styles'));
});