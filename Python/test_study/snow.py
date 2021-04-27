import turtle


def koch(size, n):
    if n == 0:
        turtle.fd(size)
    else:
        for angle in [0, 60, -120, 60]:
            turtle.left(angle)
            koch(size / 3, n - 1)


def main():
    turtle.speed(10)
    turtle.tracer(n=1.8, delay=0.5)
    turtle.bgcolor("black")
    turtle.pencolor("white")
    # turtle.fillcolor("blue")

    turtle.begin_fill()
    turtle.setup(600, 600)
    turtle.penup()
    turtle.goto(-200, 100)
    turtle.pendown()
    turtle.pensize(2)
    level = 5
    koch(400, level)
    turtle.right(120)
    koch(400, level)
    turtle.right(120)
    koch(400, level)
    turtle.end_fill()
    turtle.hideturtle()


main()
