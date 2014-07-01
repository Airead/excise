/**
 * Created by airead on 14-7-1.
 */
$(function () {
    function useUrl() {
        var runing = true;

        var gs = $('.g');
        if (gs.length) {
            runing = false;
        }

        var hrefs = $('.rc .r > a');
        hrefs.each(function (i, href) {
            var h = $(href);
            var link = h.attr('href');

            var ap = $('<a style="margin-right: 10px; background-color: greenyellow">直连</a>');
            ap.attr('href', link);
            ap.attr('target', '_blank');
            h.parent().prepend(ap);
        });

        if (runing) {
            setTimeout(useUrl, 1000)
        }
    }
    useUrl();
});