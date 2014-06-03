(function (angular) {
    "use strict";

    var tableModule = angular.module('table', []);

    tableModule.constant('DefaultTableConfiguration', {
        selectionMode: 'none',
        isGlobalSearchActivated: false,
        displaySelectionCheckbox: false,
        isPaginationEnabled: true,
        itemsByPage: 10,
        maxSize: 5,

        //just to remind available option
        sortAlgorithm: '',
        filterAlgorithm: ''
    });

    tableModule.directive('myTable', function () {
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
                console.log('ctrl.desc: ', ctrl.desc);

                var i;
                scope.$watch('columnCollection', function () {
                    for (i = 0; i < scope.columnCollection.length; i++) {
                        ctrl.insertColumn(scope.columnCollection[i]);
                    }
                });
            }
        };
    });

    tableModule.directive('smartTableGlobalSearch', function () {
        return {
            restrict: 'C',
            require: '^myTable',
            templateUrl: 'globalSearchCell.html',
            link: function (scope, element, attr, ctrl) {
                scope.searchValue = 'default';
            }
        }
    });

    tableModule.controller('TableCtrl', [
        '$scope',
        function ($scope) {
            $scope.title = 'my directive table';
            $scope.columns = [];

            this.desc = 'this is TableCtrl';

            this.insertColumn = function (columnConfig, index) {
                var config = {
                    'headerTemplateUrl': 'defaultHeader.html'
                };
                var column = angular.extend({}, columnConfig, config);

                insertAt($scope.columns, index, column);
            };

            function insertAt(arrayRef, index, item) {
                if (index >= 0 && index < arrayRef.length) {
                    arrayRef.splice(index, 0, item);
                } else {
                    arrayRef.push(item);
                }
            }
        }
    ]);
})(angular);