import click


@click.group(chain=True)
def cli():
    print 'cli start'


@cli.resultcallback()
def resultcallback(processors):
    for num in processors[0]:
        ret = num
        for processor in processors[1:]:
            ret = processor(ret)
        print ret


@cli.command()
@click.argument('input')
def init(input):
    print 'input ', input
    nums = map(int, input.split(','))

    for num in nums:
        yield num


@cli.command()
@click.option('-n', '--num', default=1)
def add(num):
    def processor(n):
        ret = n + num
        print '%s add %s return %s' % (n, num, ret)
        return ret
    return processor


@cli.command()
@click.option('-n', '--num', default=1)
def multi(num):
    def processor(n):
        ret = n * num
        print '%s multi %s return %s' % (n, num, ret)
        return ret
    return processor


@cli.command()
def show():
    def processor(n):
        if n is not None:
            print 'show %s' % n
            return n
    return processor


if __name__ == '__main__':
    cli()
