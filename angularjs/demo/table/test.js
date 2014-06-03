/**
 * Created by airead on 14-5-30.
 */
app = angular.module('mainApp', ['table']);

app.controller('TestCtl', [
    '$scope',
    function ($scope) {
        $scope.title = 'Table';

        $scope.data = [
            {'Name': 'name1', 'age': 1, 'email': 'u1@a.com'},
            {'Name': 'name2', 'age': 2, 'email': 'u2@a.com'},
            {'Name': 'name3', 'age': 3, 'email': 'u3@a.com'}
        ];

        $scope.columns = [
            {label: 'Name'},
            {label: 'age'},
            {label: 'email'}
        ]
    }
]);

