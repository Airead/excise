setwd("~/study/git-proj/excise/airscrapy/demo/tutorial/rscript")

df <- read.csv('clean_58_house.csv')

limitDate = '2014-09-01'

library('ggplot2')
mytheme = theme(text = element_text(family = 'Hei'),
                axis.text.x = element_text(angle=90, vjust=1))

barObj <- ggplot(df, aes(room, fill=room))
# barObj + geom_bar() +  mytheme

room3Df <- df[df$room == '3室',]
# drawRoom3Bar(room3Df)

ignoreTownList = c('昌平县城', '昌平周边', '小汤山', '北七家', '阳坊', 
                   '沙河', '百善', '城南')

analysis = function (df, room, county) {
  selector <- df$room == room
  selector <- selector & !is.na(df$county)
  selector <- selector & df$county == county
  selector <- selector & !is.na(df$price)
  
  tmpDf <- df[selector,]
  tmpDf
}

myFilter <- function (df) {
  selector <- df$price > 3000  # 小于这个数 不可能
  selector <- selector & df$price < 5000  # 大于5000 不会租
  selector <- selector & !df$town %in% ignoreTownList
  selector <- selector & as.character(df$time) > limitDate
  selector <- selector & !is.na(df$town)
  
  tmpDf <- df[selector,]
  tmpDf
}

getDfByTown = function (df, town) {
  selector <- df$town == town
  tmpDf <- df[selector,]
  showBox(tmpDf)
  tmpDf
}

showBox <- function (df) {
  # pdf(family='GB1',file='/tmp/a.pdf')
  p <- ggplot(df, aes(factor(town), price))
  plot(p + geom_boxplot() + geom_jitter() + xlab(as.character(df$county[1])) + mytheme)
}

showBar <- function (df) {
  p <- ggplot(df, aes(town, fill=town))
  obj <- p + geom_bar() + xlab(as.character(df$county[1])) + mytheme
  plot(obj)
}

changpingRoom3Df <- myFilter(analysis(df, '3室', '昌平'))
changpingRoom2Df <- myFilter(analysis(df, '2室', '昌平'))
haidianRoom3Df <- myFilter(analysis(df, '3室', '海淀'))
showBar(changpingRoom3Df)
showBox(changpingRoom3Df)
