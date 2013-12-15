$(document).ready(function () {
    var $selectedPlays = $('#selected-plays');
    $selectedPlays.find('> li').addClass('horizontal');
    $selectedPlays.find('li:not(.horizontal)').addClass('sub-level');
});