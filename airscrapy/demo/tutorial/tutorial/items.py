# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class TutorialItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    pass


class DmozItem(scrapy.Item):
    title = scrapy.Field()
    link = scrapy.Field()
    desc = scrapy.Field()


class HouseItem(scrapy.Item):
    url = scrapy.Field()
    title = scrapy.Field()
    price = scrapy.Field()
    paytype = scrapy.Field()
    location = scrapy.Field()
    date = scrapy.Field()
    agent = scrapy.Field()
    overview = scrapy.Field()
    addr = scrapy.Field()
    desc = scrapy.Field()
    time = scrapy.Field()
