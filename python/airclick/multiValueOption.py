import click


@click.command()
@click.option('--pos', nargs=3, type=int)
def cli(pos):
    click.echo(pos)

if __name__ == '__main__':
    cli()
