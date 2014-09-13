setwd("~/study/git-proj/excise/ml/titanic/data")
train <- read.csv("~/study/git-proj/excise/ml/titanic/data/train.csv")
test <- read.csv("~/study/git-proj/excise/ml/titanic/data/test.csv")

train$Child <- 0
train$Child[train$Age < 18] <- 1

train$Fare2 <- '30+'
train$Fare2[train$Fare < 30 & train$Fare >= 20] <- '20-30'
train$Fare2[train$Fare < 20 & train$Fare >= 10] <- '10-20'
train$Fare2[train$Fare < 10] <- '<10'

aggregate(Survived ~ Fare2 + Pclass + Sex, data=train, FUN=function(x) {sum(x)/length(x)})
