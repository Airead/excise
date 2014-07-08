import pymongo
import time

__author__ = 'airead'


def main():
    conn = pymongo.Connection(host='127.0.0.1', port=27017)
    db = conn['test']

    doc = {'_id': 1}

    db.test.insert(doc)

    time.sleep(1)

    try:
        db.test.insert(doc, w=1)
    except pymongo.errors.DuplicateKeyError as ex:
        print dir(ex)
        print ex.details
        print ex.args
        print ex.details
        print ex.message


if __name__ == '__main__':
    main()