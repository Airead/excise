setwd("~/study/git-proj/excise/airscrapy/demo/tutorial/rscript")
library(rmongodb)
mongo <- mongo.create(host="127.0.0.1", db="house")
coll <- "house.house58"

count <- mongo.count(mongo, coll)
cursor <- mongo.find(mongo, coll)

"
  _id : 2 	 http://bj.58.com/zufang/19400790073857x.shtml
	addr : 2 	 郝庄家园东区  
                            	
	title : 2 	 拎包即住的好房子,业主自住房(个人) 
	url : 2 	 http://bj.58.com/zufang/19400790073857x.shtml
	overview : 2 	 1室__1厅__1卫__30㎡__普通住宅__精装修__朝向南北__7层/7层
	price : 2 	 600
	paytype : 2 	 　押一付三
	agent : 2 	 这是经过人工审核认证的房源，100%个人出租，真实待租。
	location : 4 	 
		0 : 2 	 昌平
		1 : 2 	 郝庄家园东区

	time : 2 	 2014-09-24
	desc : 2 	 我是房东，我家
"

id <- vector('character', count)
addr <- vector('character', count)
title <- vector('character', count)
url <- vector('character', count)
overview <- vector('character', count)
price <- vector('integer', count)
paytype <- vector('character', count)
agent <- vector('character', count)
loc_1 <- vector('character', count)
loc_2 <- vector('character', count)
loc_3 <- vector('character', count)
time <- vector('character', count)
desc <- vector('character', count)
insertdate <- vector('integer', count)

getValue <- function (bson, key, default) {
  val <- mongo.bson.value(b, key)
  if (is.null(val)) {
    val = default
  }
  val
}

i <- 1
while (mongo.cursor.next(cursor)) {
  b <- mongo.cursor.value(cursor)
  id[i] <- getValue(b, '_id', 0)
  addr[i] <-getValue(b, 'addr', "")
  title[i] <- getValue(b, 'title', 0)
  url[i] <- getValue(b, 'url', "")
  overview[i] <- getValue(b, 'overview', -1)
  price[i] <- getValue(b, 'price', 0)
  paytype[i] <- getValue(b, 'paytype', 0)
  agent[i] <- getValue(b, 'agent', 0)
  tmp_loc <- getValue(b, 'location', c('', '', ''))
  loc_1[i] <- tmp_loc[1]
  loc_2[i] <- tmp_loc[2]
  loc_3[i] <- tmp_loc[3]
  # cat(loc_1[i], loc_2[i], loc_3[i])
  time[i] <- getValue(b, 'time', 0)
  desc[i] <- getValue(b, 'desc', 0)
  insertdate[i] <- getValue(b, 'insertdate', 0)
  
  i <- i+1
}
insertdate <- as.POSIXlt(insertdate - 8 * 60 * 60, origin='1970-01-01 00:00:00')
results <- as.data.frame(list(id=id, 
                              addr=addr,
                              title=title,
                              url=url,
                              overview=overview,
                              price=price,
                              paytype=paytype,
                              agent=agent,
                              loc_1=loc_1,
                              loc_2=loc_2,
                              loc_3=loc_3,
                              time=time,
                              desc=desc,
                              insertdate=insertdate))

results$price <- as.integer(as.character(results$price))

tmp_room <- strsplit(as.character(results$overview), '__')
room <- vector('character', length(tmp_room))
i <- 1;
while (i < length(tmp_room)) {
  room[i] <- tmp_room[[i]][1]
  i <- i + 1
}

write.csv(results, 'raw_58_house.csv', row.names=F)

cleanDf <- data.frame(list(id=results$id,
                           addr=addr,
                           room=room,
                           price=results$price,
                           county=results$loc_1,
                           town=results$loc_2,
                           time=results$time,
                           insertdate=results$insertdate,
                           desc=results$desc))
write.csv(cleanDf, 'clean_58_house.csv', row.names=F)

