/**
 * Created by airead on 14-5-30.
 */
app = angular.module('mainApp', ['table']);

app.controller('TestCtl', [
    '$scope',
    function ($scope) {
        $scope.title = 'Table'
    }
]);

