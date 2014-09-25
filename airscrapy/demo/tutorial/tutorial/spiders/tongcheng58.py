# -*- coding: utf-8 -*-
from datetime import datetime
import random
import scrapy
from scrapy.shell import inspect_response
import pymongo

DB = 'house'
COLLNAME = 'house58'

connection = pymongo.Connection(host='127.0.0.1', port=27017)
db = connection[DB]
house_coll = db[COLLNAME]

from tutorial.items import HouseItem


class Tongcheng58Spider(scrapy.Spider):
    name = "58"

    download_delay = 5

    allowed_domains = ["58.com"]
    start_urls = (
        'http://bj.58.com/zufang/0/',
        'http://bj.58.com/changping/zufang/0/j3/'
    )

    base_url = 'http://bj.58.com'

    def parse(self, response):
        self.log("xpath %s" % response.xpath('//a[@class="next"]/@href').extract())
        next_link = response.xpath('//a[@class="next"]/@href').extract()
        if len(next_link) == 1:
            next_link = ''.join([Tongcheng58Spider.base_url, next_link[0]])
        # inspect_response(response, self)

        detail_links = response.xpath('//h1/a[contains(@href, "shtml")]/@href').extract()

        for link in detail_links:
            # link = ''.join([Tongcheng58Spider.base_url, link])
            if self.is_url_exist(link):
                self.log('link %s have existed' % link)
                continue
            yield scrapy.Request(link, callback=self.parse_detail)

        if next_link:
            self.log('parse url: %s' % next_link)
            yield scrapy.Request(next_link)

    def parse_detail(self, response):
        self.log('parser detail %s, time %s:' % (response.url, datetime.now()))
        self.random_delay()

        # inspect_response(response, self)

        item = HouseItem()

        agent = ''
        try:
            agent = response.xpath('//h1/@title').extract()[0]
        except IndexError:
            pass

        title = response.xpath('//h1/text()').extract()[0]

        price_type = response.xpath('(//ul/li/div[@class="su_con"])[1]/span/text()').extract()
        price = price_type[0]
        paytype = '无'
        if len(price_type) > 1:
            paytype = price_type[1]
        overview = response.xpath('(//ul/li/div[@class="su_con"])[2]/text()').extract()[0]
        overview = '__'.join(overview.split())
        location = response.xpath('(//ul/li/div[@class="su_tit"])[3]/following-sibling::a/text()').extract()
        addr = response.xpath('(//ul/li/div[@class="su_tit"])[4]/following-sibling::div/text()').extract()[0]
        desc = response.xpath('//div[@class="description_con "]/p/text()').extract()[0]
        desc = ' '.join(desc.split())
        time = response.xpath('//li[@class="time"]/text()').extract()[0]
        time = ''.join(time.split())

        item['url'] = response.url
        item['agent'] = agent
        item['title'] = title
        item['price'] = price
        item['paytype'] = paytype
        item['overview'] = overview
        item['location'] = location
        item['addr'] = addr
        item['desc'] = desc
        item['time'] = time
        item['insertdate'] = datetime.now()
        self.mongo_save(item)

        return item

    def mongo_save(self, obj):
        search = {'_id': obj['url']}
        house_coll.update(search, dict(obj), upsert=True)

    def is_url_exist(self, url):
        search = {'_id': url}
        return house_coll.find(search).count()

    def random_delay(self):
        Tongcheng58Spider.download_delay = 5 + (random.randint(1, 5000) / 1000.0)
