app = angular.module('app', []);

app.controller('ParentCtl', [
    '$scope',
    function ($scope) {
        $scope.name = 'Parent'
    }
]);

app.directive('testScope', function () {
    return {
        restrict: 'E',
        replace: true,
        scope: {
            equalName: '=',
            atName: '@',
            quoteName: '&'
        },
        templateUrl: 'temp.html'
    }
});