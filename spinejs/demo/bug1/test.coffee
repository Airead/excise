class Test extends Spine.Controller
  constructor: ->
    super
    @testReplace()

  testReplace: =>
    console.log 'before @el', @el.html()
    console.log 'before @$el', @$el.html()
    console.log 'replace by replaced'
    @.replace '<div>replaced</div>'
    console.log 'after @el', @el.html()
    console.log 'after @$el', @$el.html()

$ ->
  new Test {el: '#test'}