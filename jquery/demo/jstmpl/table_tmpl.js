$(document).ready(function () {
    var $commonTableTmp = $('#common-table-template');

    var headers = ['name', 'gender', 'age'];
    var rows = [
        ['Airead Fan', 'male', '26'],
        ['Ning Li', 'female', '24'],
        ['The other', 'none', 'min']
    ];

    var table_data = {
        headers: headers,
        rows: rows
    };

    var html = $.parseTemplate($commonTableTmp.html(), table_data);

    console.log(html);
    $('body').append(html);
});