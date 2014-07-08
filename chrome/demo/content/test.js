/**
 * Created by airead on 14-7-1.
 */
$(function () {
    function useUrl() {
        var needAdd = $('#my-directly-google');

        if (needAdd.length == 0) {
            var hrefs = $('.rc .r > a');
            hrefs.each(function (i, href) {
                var $h = $(href);
                var link = $h.attr('href');

                var $div = $('<div id="my-directly-google" style="display: inline-block;"></div>');
                var $ap = $('<a style="margin-right: 10px; background-color: greenyellow">直连</a>');
                $ap.attr('href', link);
                $ap.attr('target', '_blank');
                $div.html($ap);

                $h.parent().prepend($div);
            });
        }

        setTimeout(useUrl, 3000)
    }

    useUrl();
});