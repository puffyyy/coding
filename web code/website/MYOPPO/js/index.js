$(window).scroll(function () {
    var scrollT = document.documentElement.scrollTop || document.body.scroll
    // console.log(scrollT);
    var backT = $('#world').offset().top - $(window).height() / 2;
    // console.log(backT);
    if (scrollT > backT) {
        $(".a1").addClass("animated bounceInRight show").removeClass("fade");
        $(".a2").addClass("animated bounceInLeft show").removeClass("fade");
        $(".a3").addClass("animated bounceInUp show").removeClass("fade");
        $(".a4").addClass("animated bounceInDown show").removeClass("fade");
    }
})