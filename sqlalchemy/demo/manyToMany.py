from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, ForeignKey
from sqlalchemy.orm import relationship, sessionmaker

__author__ = 'airead'

engine = create_engine('sqlite:///:memory:', echo=True)

Session = sessionmaker(bind=engine)
session = Session()


Base = declarative_base()


class ParentChild(Base):
    __tablename__ = 'parent_child'

    parent_id = Column(Integer, ForeignKey('parent.id'), primary_key=True)
    child_id = Column(Integer, ForeignKey('child.id'), primary_key=True)


class Parent(Base):
    __tablename__ = 'parent'
    id = Column(Integer, primary_key=True)
    children = relationship('ParentChild', backref='parent')

    def __repr__(self):
        return '<Parent %s>' % self.id


class Child(Base):
    __tablename__ = 'child'
    id = Column(Integer, primary_key=True)
    parents = relationship('ParentChild', backref='child')

    def __repr__(self):
        return '<Child %s>' % self.id


def add_parent(uid):
    p = Parent(id=uid)
    session.add(p)
    session.commit()


def add_child(uid):
    c = Child(id=uid)
    session.add(c)
    session.commit()


def add_parent_child(pid, cid):
    p_c = ParentChild(parent_id=pid, child_id=cid)
    session.add(p_c)
    session.commit()


def main():
    print 'hello oneToMany'
    print 'Parent: ', repr(Parent.__table__)
    print 'Child: ', repr(Child.__table__)

    Base.metadata.create_all(engine)

    add_parent(1)
    add_parent(2)
    add_child(1)
    add_child(2)
    add_parent_child(1, 2)
    add_parent_child(1, 1)
    add_parent_child(2, 1)

    print '---query parents---'
    query = session.query(Parent)
    parents = query.all()

    for parent in parents:
        print '====='
        print 'parent: ', parent
        print parent.children
        for assoc in parent.children:
            print assoc.child

    print
    print '---query childs---'
    childs = session.query(Child).all()
    for child in childs:
        print '====='
        print 'child: ', child
        print child.parents
        for assoc in child.parents:
            print assoc.parent

if __name__ == '__main__':
    main()
