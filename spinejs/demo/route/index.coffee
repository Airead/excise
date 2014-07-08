class App extends Spine.Controller
  constructor: ->
    super
    @routes
      '/users/:id': (params) ->
        console.log '/users/', params.id
      '/users': ->
        console.log '/users'
        @navigate '/users', 1

    @$el.append 'run'

Spine.Route.setup()

$ ->
  window.app = new App {el: '#main'}