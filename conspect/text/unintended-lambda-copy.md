Comment to `conspect/src/lambdas/unintended-lambda-copy.cpp`

When *std::function* is created with a lambda, the std::function internally makes a copy of the lambda object. Thus, our call to *fn()* is actually being executed on the copy of our lambda, not the actual lambda.

If we need to pass a mutable lambda, and want to avoid the possibility of inadvertent copies being made, there are two options. One option is to use a non-capturing lambda instead -- in the above case, we could remove the capture and track our state using a static local variable instead. But static local variables can be difficult to keep track of and make our code less readable. A better option is to prevent copies of our lambda from being made in the first place. But since we can’t affect how std::function (or other standard library functions or objects) are implemented, how can we do this?

Fortunately, C++ provides a convenient type (as part of the `<functional>` header) called `std::ref` that allows us to pass a normal type as if it were a reference. By wrapping our lambda in a *std::ref*, whenever anybody tries to make a copy of our lambda, they’ll make a copy of the reference instead, which will copy the reference rather than the actual object.

We should update the call of the *invoke()* function to this:

`invoke(std::ref(count));`

The output won't change even if we make *invoke()* take *fn* by value instead of by ref.

**Best practise**: it's better to avoid lambdas with states altogether. Stateless lambdas are easier to understand and don’t suffer from the issues described in this and .cpp files, as well as more dangerous issues that arise when you add parallel execution.