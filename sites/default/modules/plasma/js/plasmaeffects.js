(function ($) {
  var plasma;

  Drupal.plasma = function() {
    var $messages  = $('#messages');
    var ren = /rgb\((\d+), *(\d+), *(\d+)\) +(\d+)px +(\d+)px +(\d+)px +(\d+)px/;
    var rei = /rgb\((\d+), *(\d+), *(\d+)\) +(\d+)px +(\d+)px +(\d+)px +(\d+)px, rgb\((\d+), *(\d+), *(\d+)\) +(\d+)px +(\d+)px +(\d+)px +(\d+)px inset/;

/*  function fadeShadow () {
      if (dir > 0) {
        mblur++;
        dir = (dir > 10) ? dir = -1 : dir + 1;
        hsl[0] = (hsl[0] > deg - cinc) ? hsl[0] + cinc - deg : hsl[0] + cinc;
      } else {
        mblur--;
        dir = (dir < -10) ? dir = 1 : dir - 1;
        hsl[0] = (hsl[0] < 0 + cinc) ? hsl[0] - cinc + deg : hsl[0] - cinc;
      }
      var rgb = hslToRgb(hsl[0],hsl[1],hsl[2]);
      var nshadow = '0 0 ' + mblur + 'px ' + mspread + 'px ' +
                    'rgb(' + parseInt(rgb[0]) + ',' + parseInt(rgb[1]) + ',' + parseInt(rgb[2]) + ')';
      $header.css({boxShadow: nshadow});
//    $messages.append('<p>nshadow ' + dir + ' ' + hsl[0] + ' ' + nshadow + '</p>');
//    $header.css({boxShadow: '0 0 ' + mblur + 'px ' + mspread + '1px ' +
//                 border: 'solid 2px #00ff00'});
    } */


    function getDelay(min,max) {
      var delay = Math.ceil(Math.random()*(max-min)+min); 
//    $messages.append('<p>getDelay ' + delay + ' ' + max + ' ' + min + '</p>');
      return delay; 
    }

    function flashShadow($elem,delay) {
//      $elem.delay = delay;
      $elem.each(flashElem);
    }

    function flashElem(index, elem) {
      var delay = 1000;
      var boxShadow = $(this).css("boxShadow");
//      $messages.append('<p>flashElem initial ' + boxShadow + '</p>');

      var hasInset = 0;
      var matches;
      var re;
      var cs;
      if (boxShadow.indexOf('inset') != -1) {
        hasInset = 1;
        re = rei
      } else {
        re = ren;
        cs = '0 0 0 0 ' + rgbo;
      }
      matches = boxShadow.match(re);
      if (matches && matches.length) {
        var state = 0;
        // 1 red, 2 green, 3 blue
        // 4 horiz, 5 vert, 6 blur, 7 spread
        // 8 red, 9 green, 10 blue
        // 11 horiz, 12 vert, 13 blur, 14 spread
        var rgbo = 'rgb(' + parseInt(matches[1]) + ',' + parseInt(matches[2]) + ',' + parseInt(matches[3]) + ')';
        cs = '0 0 0 0 ' + rgbo;
        if (hasInset) {
          var rgbi = 'rgb(' + parseInt(matches[8]) + ',' + parseInt(matches[9]) + ',' + parseInt(matches[10]) + ') inset';
          cs += ', 0 0 0 0 ' + rgbi;
        }
//        var hsl = rgbToHsl(matches[1],matches[2],matches[3]);
        var nflash = getDelay(2,20);
        if (nflash == 4) nflash = getDelay(10,20);
//        var nflash = 20;
        $(this).css({boxShadow: cs});
//        $messages.append('<p>initial ' + matches[8] + ' ' + matches[9] + '</p>');

        var $that = $(this);
        setTimeout(function() {
          setTimeout(function flashIt() {
            var nshadow;
            if (state || nflash == 1) {
              state = 0;
              nshadow = '0 0 ' + matches[6] + 'px ' + matches[7] + 'px ' + rgbo;
              if (hasInset)
                  nshadow += ', 0 0 ' + matches[13] + 'px ' + matches[14] + 'px ' + rgbi;
              $that.css({boxShadow: nshadow});
            } else {
              state = 1;
              $that.css({boxShadow: cs});
            }
//            $messages.append('<p>flash ' + nshadow + '</p>');
            if (--nflash > 0) {
              setTimeout(flashIt,getDelay(20,150));
            }
          },getDelay(20,120));
        },getDelay(200,1500));
      } else {
//        $messages.append('<p>no match</p>');
     }
    }

    function initPlasma() {
      flashShadow($('#header'),getDelay(550,1000));
//    flashShadow($('#superfish-1 li a'),getDelay(100,1000));
//    flashShadow($('#footer'),getDelay(300,2000));
//    flashShadow($('.view-filters .views-exposed-widget'),getDelay(500,750));
//    flashShadow($('div.views-row'),getDelay(0,750));
//      flashShadow($sysmonitor,getDelay(500,2000));
    }
    return {
      init : initPlasma,
    }
  };

  Drupal.behaviors.plasma = {
    attach: function (context, settings) {
      $('#header').once(function() {
        plasma = Drupal.plasma();
        plasma.init();
      });
//    plasma.attach();
    },
  };
})(jQuery);
