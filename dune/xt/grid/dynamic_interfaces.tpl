#include "{{include_file}}"

{% for c in classes %}
    class {{c.name}}Interface {
    {% for f in c.functions %}
        {{ f.declaration }}
        {
            WRAPPEDTYPE->{{f.name}}({% for param in f.parameters -%} {{ param }}{{ "," if not loop.last }} {%- endfor -%});

        }
    {% endfor %}
    };
{% endfor %}



