/**
 * Created by airead on 14-4-17.
 */
var kue = require('kue');
var jobs = kue.createQueue();

jobs.create('email', {
    title: 'welcome email for tj'
  , to: 'tj@learnboost.com'
  , template: 'welcome-email'
}).save();