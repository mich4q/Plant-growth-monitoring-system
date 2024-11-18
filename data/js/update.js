function dropHandler(ev) {
	$(".box").removeClass('dragging');
	$(".box:not(#drop_zone)").hide();
	console.log('File(s) dropped');
	var lang = $('html').attr('lang');
	//$('#update_text').text(translator.translate("update_text_upload")); //todo: fix this
	$('#update_text').text('Update started');
	ev.preventDefault();
	if (ev.dataTransfer.items) {
		[...ev.dataTransfer.items].forEach((item, i) => {
			if (item.kind === 'file') {
				const file = item.getAsFile();
				console.log(`… file[${i}].name = ${file.name}`);
				let url = "/update";
				let needsReboot = true;
				var fd = new FormData();
				fd.append('file', file);
				$.ajax({
					url: url,
					type: 'post',
					data: fd,
					contentType: false,
					processData: false,
					success: function (response) {
						if (response != 0) {
							console.log('file uploaded');
							if (needsReboot) {
								$('#update_text').text('Upload done, rebooting');
								setTimeout(function () { location.reload(); }, 5000);
							} else {
								location.reload();
							}
						}
						else {
							console.log('file not uploaded');
							$('#update_text').text('Upload Error');
							setTimeout(function () { location.reload(); }, 5000);
						}
					},
				});
			}
		});
	} else {
		[...ev.dataTransfer.files].forEach((file, i) => {
			console.log(`… file[${i}].name = ${file.name}`);
		});
	}
}
function dragOverHandler(ev) {
	ev.preventDefault();
	$(".box").addClass('dragging');
}