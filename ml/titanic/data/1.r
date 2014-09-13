setwd("~/study/git-proj/excise/ml/titanic/data")
train <- read.csv("~/study/git-proj/excise/ml/titanic/data/train.csv")
test <- read.csv("~/study/git-proj/excise/ml/titanic/data/test.csv")

test$Survived <- rep(0, 418)
submit <- data.frame(PassengerId = test$PassengerId, Survived = test$Survived)
write.csv(submit, file = "theyallperish.csv", row.names = FALSE)
