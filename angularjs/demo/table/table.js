(function (angular) {
    "use strict";

    var tableModule = angular.module('table', []);

    tableModule.directive('myTable', function () {
        var config = {
            selectionMode: 'none',
            isGlobalSearchActivated: false,
            displaySelectionCheckbox: false,
            isPaginationEnabled: true,
            itemsByPage: 10,
            maxSize: 5,

            //just to remind available option
            sortAlgorithm: '',
            filterAlgorithm: ''
        };

        return {
            restrict: 'EA',
            scope: {
                columnCollection: '=columns',
                dataCollection: '=rows',
                config: '='
            },
            replace: 'true',
            templateUrl: 'smartTable.html',
            controller: 'TableCtrl',
            link: function (scope, element, attr, ctrl) {
                console.log('ctlr.desc: ', ctrl.desc);
            }
        };
    });

    tableModule.controller('TableCtrl', [
        '$scope',
        function ($scope) {
            $scope.title = 'my directive table';

            this.desc = 'this is TableCtrl';
        }
    ]);
})(angular);