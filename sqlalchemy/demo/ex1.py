from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String

__author__ = 'airead'


engine = create_engine('sqlite:///:memory:', echo=True)


Base = declarative_base()


class User(Base):
    __tablename__ = 'users'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    fullname = Column(String)
    password = Column(String)

    def __repr__(self):
        return "<User %s>" % id

if __name__ == '__main__':
    print 'hello ex1'
    print User.__table__
    Base.metadata.create_all(engine)
    print repr(User.__table__)
