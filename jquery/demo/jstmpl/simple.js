$(document).ready(function () {
    $('#test').click(function () {
        var $item = $('#ItemTemplate');
        var html;
        for (var i = 0; i < 3; i++) {
            var data = {
                name: 'Airead - ' + i.toString(),
                address: {
                    street: 'Fan - ' + (i + 10).toString(),
                    city: 'Beijing'
                }
            };
            html = $.parseTemplate($item.html(), data);
            $('body').append(html);
        }
    });
});