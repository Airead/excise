Todos.TodoController = Ember.ObjectController.extend({
    isCompleted: function (key, value) {
        var model = this.get('model');

        if (value === undefined) {
            return model.get('isCompleted');
        } else {
            model.set('isCompleted', value);
            model.save();
            return value;
        }
    }.property('model.isCompleted')
});