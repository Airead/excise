class Animal
  constructor: (name) ->
    @name = name

animal = new Animal('Parrot')
console.log "Animal is a #{animal.name}"