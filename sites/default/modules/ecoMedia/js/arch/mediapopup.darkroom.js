(function ($) {
  Drupal.behaviors.mediapopup = {
    attach: function (context, settings) {
      var $messages  = $('#messages');
      var images = new Array();
      var nimages = 0;
      var mode = 0; // 0 view, 1 view/lock, 2 edit
      var $imageDarkroom;
      var $imagePopup;
      var imageSrc;
      var dkrm;

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
      $('.ds-images a').click(function(ev) {
        console.debug(".ds-images a -  click");
        ev.stopPropagation();
      });

      function setMode(newmode) {
        mode = newmode;
        switch (newmode) {
          case 0: 
            $('#modebuttons #mode-view').addClass('checked');
            $('#modebuttons #mode-edit').removeClass('checked');
            $('#modebuttons #mode-frame').removeClass('checked');
            break;
          case 1: 
            $('#modebuttons #mode-view').removeClass('checked');
            $('#modebuttons #mode-edit').addClass('checked');
            $('#modebuttons #mode-frame').removeClass('checked');
            break;
          case 2: 
            $('#modebuttons #mode-view').removeClass('checked');
            $('#modebuttons #mode-edit').removeClass('checked');
            $('#modebuttons #mode-frame').addClass('checked');
            var cropPlugin = dkrm.getPlugin('crop');
            cropPlugin.selectZone(150, 25, 400, 400);
            break;
        };
      };

      function findImage(src,offset) {
        for(i=0; i < nimages; i++) {
          if (src == images[i]) {
            if (offset == 1) {
              if (++i == nimages) i = 0;
            } else {
              if (--i == -1) i = nimages-1;
            }
            imageSrc = images[i];
            return images[i];
          }
        }
        return;
      };

      function dispImage(src,ev) {
        newImage = new Image(); // create the new image
        newImage.onload = function() {
          var dw = $(window).width() - 400;
          var dh = $(window).height() - 30;
          dkrm.setImage(newImage,undefined,dh);
  
          var elem = document.querySelector('#image');
//          dkrm.setImage(src);
//          alert('image ' + nw + 'x' + nh + 
//                '\ncurrent image ' + iw + 'x' + ih + 
//                '\nnew size ' + fw + 'x' + fh +
//                '\nwindow size ' + dw + 'x' + dh);
          if (ev) {
            if (ev.pageX < dw / 2) {
              $imagePopup.addClass('right');
            } else {
              $imagePopup.removeClass('right');
            }
          }
          $imagePopup.removeClass('hide');
        };
        newImage.src = src;     // This preloads the image, must be after onload()
      };


      function initImages() {
        // Create a list of images on the screen
           
        // Add the imageDarkroom div and img to page
        // This would be best done in Drupal by modifying the form 
        $('#page').append('<div id="image-popup" class="hide">' +
                            '<div id="popupbuttons">' + 
                              '<div id="imagebuttons">' + 
                                '<div>Image</div>' +
                                '<img id="image-left" src="/sites/all/icons/left_arrow.png"></img><br>' + 
                                '<img id="image-right" src="/sites/all/icons/right_arrow.png"></img><br>' + 
                              '</div>' +
                              '<div id="modebuttons">' + 
                                '<div>Mode</div>' +
                                '<img id="mode-view" class="checked" src="/sites/all/icons/eye.png"></img><br>' + 
                                '<img id="mode-edit"  src="/sites/all/icons/eye.png"></img><br>' + 
                                '<img id="mode-frame" src="/sites/all/icons/frame.png"></img><br>' + 
                              '</div>' +
                              '<div id="viewbuttons">' + 
                                '<div>View</div>' +
                                '<img id="view-zoom" src="/sites/all/icons/zoom.png"></img><br>' + 
                                '<img id="view-zoomin" src="/sites/all/icons/zoomin.png"></img><br>' + 
                                '<img id="view-zoomout" src="/sites/all/icons/zoomout.png"></img><br>' + 
                              '</div>' +
                              '<div id="editbuttons">' + 
                                '<div>Edit</div>' +
                                '<img id="edit-crop" src="/sites/all/icons/scissors.png"></img><br>' + 
                                '<img id="edit-scale" src="/sites/all/icons/scale.png"></img><br>' + 
                                '<img id="edit-color" src="/sites/all/icons/color_wheel.png"></img><br>' + 
                                '<img id="edit-left" src="/sites/all/icons/rotate-left.png"></img><br>' + 
                                '<img id="edit-right" src="/sites/all/icons/rotate-right.png"></img>' + 
                              '</div>' + 
                              '<div id="filebuttons">' + 
                                '<div>File</div>' +
                                '<img id="file-view" src="/sites/all/icons/view.png"></img><br>' + 
                                '<img id="file-edit" src="/sites/all/icons/edit.png"></img><br>' + 
                                '<img id="file-delete" src="/sites/all/icons/delete.png"></img><br>' + 
                                '<img id="file-download" src="/sites/all/icons/download.png"></img><br>' + 
                                '<img id="file-save" src="/sites/all/icons/floppy.png"></img><br>' + 
                              '</div>' +
                            '</div>' + 
                            '<div id="image-darkroom">' +
                              '<img id="image" src="#"></img>' +
                            '</div>' +
                          '</div>');


        $imagePopup = $('#image-popup');
        $imageDarkroom = $('#image-darkroom');

        dkrm = new Darkroom('#image-darkroom', {
        // Size options
          minWidth: 100,
          minHeight: 100,
        
          plugins: {
            //save: false,
            crop: {
              minHeight: 50,
              minWidth: 50,
              ratio: 1
            }
          },
          init: function() {
//          var cropPlugin = this.getPlugin('crop');
//          cropPlugin.selectZone(170, 25, 500, 500);
//          cropPlugin.requireFocus();
          }
        });

        // click on #image-darkroom - hide it, set mode back to view=0
        $imageDarkroom.click(function () {
          console.debug("#image-darkroom - click");
          if (mode > 0) return;   // James - this is temporary, 
          $imagePopup.addClass('hide');
//        setMode(0);
        });
        // mouse enters the #image-darkroom div - do nothing
        $imagePopup.mouseenter(function() {
          console.debug('#image-darkroom mouseenter');
        });
        // mouse leaves the #image-darkroom div - hide it
        $imagePopup.mouseleave(function() {
          console.debug('#image-darkroom mouseleave');
          if (mode > 0) return false;
          $imagePopup.addClass('hide');
        });
        // click on #image-left - bring up next image to the left
        $('#image-left').click(function() {
          console.debug('#image-left click');
          setMode(1);
          dispImage(findImage(imageSrc,-1));   // James get image from dkrm
        });
        // click on #image-right - bring up next image to the right
        $('#image-right').click(function() {
          console.debug('#image-right click');
          setMode(1);
          dispImage(findImage(imageSrc,1));      // get image source from dkrm
        });
        // click on #mode-view - set mode back to view=0
        $('#mode-view').click(function() {
          setMode(0);
        });
        // click on #mode-view - set mode to edit=1
        $('#mode-edit').click(function() {
          setMode(1);
        });
        $('#mode-frame').click(function() {
          setMode(2);
        });

        // stop propogation of buttons from reaching #image-darkroom
        $('#image-darkroom').click(function (ev) {
          ev.stopPropagation();
        });
        $('#popupbuttons').click(function (ev) {
          ev.stopPropagation();
        });

        // cycle through each thumbnail on the page that has the 
        // css selector: .views-row a img
//      $('.views-row a img').each(function(index,value) {   // Find all .views-rows's that have a link <a> and an image <img>
        $('.image-style-ds-thumbnail').each(function(index,value) {   // Find all .views-rows's that have a link <a> and an image <img>
          images[nimages++] = $(this).parent().attr('href'); // the parent element MUST be a link to the image to load
          $(this).parent().unbind('click');
          // When user clicks on a thumbnail, set program to ignore mouseleave event
          $(this).click(function() {
            if (mode > 0) {
              setMode(0);
            } else {
              setMode(1);
            }
            return false;
          });
          $(this).parent().click(function() {
            setMode(1);
            return false;
          });

          $('#file-save').click(function () {
            var dataUrl = dkrm.canvas.toDataURL();
            $.ajax({
              type: "POST",
              url: "save.php",
              data: { 
                src: "somesrc",
                imgBase64: dataUrl
              }
            });
          });

          // when the mouse enters a thumbnail image
          // un-hide div#image-darkroom and display new image
          var sleep = 0;
          var timer;
          $(this).hoverIntent({
            over: function(ev) {
              console.debug("image mouseenter " + imageSrc);
              if (mode > 0) return false;
              var $that = $(this);
              timer = setTimeout(function() {
                imageSrc = $that.parent().attr('href'); // the parent element MUST be a link to the image to load
                setMode(0);
                dispImage(imageSrc,ev);
              },250);
            },
            out: function(ev) {
              if (mode > 0) return false;
              clearTimeout(timer);
              var el = ev.relatedTarget ? ev.relatedTarget : ev.toElement;
              var el1 = $(el).closest('#image-popup');
              console.debug('image mouseleave ');
              if (el === $imagePopup[0] || el1.length) {
                console.debug("image mouseleave image has focus");
              } else {
                $imagePopup.addClass('hide');
                setMode(0);
                console.debug("image mouseleave image doesn't have focus ");
              }
            },
            sensitivity: 50,
            interval: 50
          });
        });
      }

      initImages();
    }
  } 
})(jQuery);
