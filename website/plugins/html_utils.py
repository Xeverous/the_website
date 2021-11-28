def escape_text_into_html(text: str) -> str:
    # https://stackoverflow.com/a/49329235/4818802
    return text.replace('&', '&amp;').replace('>', '&gt;').replace('<', '&lt;'
        ).replace('\'','&#39;').replace('"','&#34;')
