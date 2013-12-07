/**
 * Created by airead on 13-11-25.
 */

$(document).ready(function () {
    var all = $('#checkAll');
    var subBoxes = $('input[name="test"]');

    all.click(function () {
        subBoxes.prop('checked', this.checked);
    });

    subBoxes.click(function () {
        var val = subBoxes.length == subBoxes.filter(":checked").length;
        all.prop("checked", val);
    });


});

function showChecked() {
    console.log("showChecked()");

    var subBoxes = $('input[name="test"]');
    var vals = [];

    subBoxes.each(function () {
        if (this.checked) {
            vals.push(this.value);
        }
    });

    console.log(vals);
}