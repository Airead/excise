$ = jQuery

class Task extends Spine.Model
  @configure 'Task', 'name', 'done'


class Tasks extends Spine.Controller
  events:
    'change input[type=checkbox]': 'toggle'
    'click .destroy': 'remove'
    'dblclick .view': 'edit'
    'keypress input[type=text]': 'blurOnEnter'
    'blur input[type=text]': 'close'

  elements:
    'input[type=text]': 'input'

  constructor: ->
    super
    @item.bind 'update', @render
    @item.bind 'destroy', @release

  render: =>
    console.log 'render'
    template = '''
    <div class="item {{#done}}done{{/done}}">
        <div class="view" title="Double click to edit...">
            <input type="checkbox" {{#done}}checked="checked"{{/done}} >
            <span>{{name}}</span> <a class="destroy"></a>
        </div>

        <div class="edit">
            <input type="text" value="{{name}}">
        </div>
    </div>
    '''
    @replace Mustache.render template, @item
    @

  toggle: ->
    @item.done = !@item.done
    @item.save()

  remove: ->
    console.log 'remove'
    @item.destroy()
    console.log 'records', @item.constructor.records

  edit: ->
    console.log 'edit'
    @$el.addClass('editing')
    @input.focus()

  blurOnEnter: (e) ->
    if e.keyCode is 13 then e.target.blur()

  close: ->
    @$el.removeClass 'editing'
    @item.updateAttributes {name: @input.val()}


class TaskApp extends Spine.Controller
  events:
    'submit form': 'create'

  elements:
    '.items': 'items'
    'form input': 'input'

  constructor: ->
    super
    Task.bind 'create', @addOne
    Task.fetch()

  addOne: (task) =>
    console.log 'add task', task
    view = new Tasks {item: task}
    @items.append view.render().el

  create: (e) ->
    e.preventDefault()
    Task.create {name: @input.val()}
    console.log 'Task', Task.records
    @input.val ''


$ ->
  window.app = new TaskApp(el: $('#tasks'))