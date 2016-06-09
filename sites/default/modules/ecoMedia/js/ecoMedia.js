(function ($) {
  Drupal.behaviors.ecoMedia = {
    attach: function (context, settings) {
      // highlight the entire background when vbo-select changes
//    $(".vbo-select").on("input", function () {
//      if ($(this).attr('checked')) {
//        $(this).closest('.views-row').addClass('checked');
//      } else {
//        $(this).closest('.views-row').removeClass('checked');
//      }
//      return;
//    });

      $('.vbo-select-this-page').change(function () {
        if ($(this).attr('checked')) {
          $('.views-row').addClass('checked');
        } else {
          $('.views-row').removeClass('checked');
        }
      });

      $('.ds-images .views-row').click(function () {
        var $select = $(this).find('.vbo-select');
        if ($select.attr('checked')) {
          $select.attr('checked',false);
          $(this).removeClass('checked');
        } else {
          $select.attr('checked',true);
          $(this).addClass('checked');
        }
      });
    }
  } 
})(jQuery);
