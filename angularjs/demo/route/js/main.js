var app = angular.module('myRouteApp', []);

app.config(['$routeProvider', function ($routeProvider) {
    $routeProvider.when('/', {
        conntroller: 'HomeController',
        template: '<h2>We are home</h2>'
    }).when('/:name', {
            controller: 'NameController',
            templateUrl: 'sub.html'
        }
    ).otherwise(
        {redirectTo: '/'}
    );
}]);

app.controller('NameController', ['$scope', function ($scope, $routeParams) {
    //$scope.name = $routeParams.name;
    $scope.name = '111';
}]);