import click


@click.group(chain=True)
def cli():
    print 'cli start'


@cli.resultcallback()
def resultcallback(processors):
    nums = processors[0]
    for processor in processors[1:]:
        processor(nums)

    print 'results: '
    for num in nums:
        print 'num: %s' % num


@cli.command()
@click.argument('input')
def init(input):
    print 'input ', input
    return map(int, input.split(','))


@cli.command()
@click.option('-n', '--num', default=1)
def add(num):
    def processor(nums):
        for i in xrange(len(nums)):
            nums[i] += num
        print 'add %s, results: %s' % (num, nums)
    return processor


@cli.command()
@click.option('-n', '--num', default=1)
def multi(num):
    def processor(nums):
        for i in xrange(len(nums)):
            nums[i] *= num
        print 'multi %s, results: %s' % (num, nums)
    return processor

if __name__ == '__main__':
    cli()
