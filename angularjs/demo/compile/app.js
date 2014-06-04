var app = angular.module('mainApp', []);

app.controller('TestCtl', function ($scope) {
    $scope.foo = {
        'bar': 123,
        'name': 'foo'
    };

    $scope.bar = {
        'foo': 456,
        'name': 'something else'
    };
});

app.directive('whatIsInThese', ['$compile', function ($compile) {
    return function (scope, elem, attrs) {
        //getting a list of space-separated property names
        //from the attribute.
        var these = attrs.whatIsInThese.split(' ');

        var pre = angular.element('<pre></pre>');

        var content = '';
        //append a bunch of bound values from the list.
        angular.forEach(these, function (item) {
            content += '{{' + item + '| json}}\n\n';
        });

        pre.html(content);

        elem.append(pre);

        //bind our view to the scope!
        //(try commenting out this line to see what happens!)
        //compiled(scope);

        $compile(pre)(scope)
    };
}]);